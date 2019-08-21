#include <cstdio>
#include <cstdlib>
#include <memory>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>

  static MYSQL* MySQLInit(){
    MYSQL* connect_fd = mysql_init(NULL);
    if(mysql_real_connect(connect_fd,"127.0.0.1","root","","blog_system",3306,NULL,0) == NULL){
      printf("连接失败!%s\n",mysql_error(connect_fd));
      return NULL;
    }
    mysql_set_character_set(connect_fd,"utf8");
    return connect_fd;
  }

  static void MYSQLRelease(MYSQL* mysql){
    mysql_close(mysql);
  }

  class BlogTable{
    public:
      BlogTable(MYSQL* mysql):mysql_(mysql){}

      bool Insert(const Json::Value& blog){
        const std::string& content = blog["content"].asString();
        //由于博客内容可能包含一些特殊字符(\n,'',""等)，会导致拼装出的sql语句有问题
        //应该使用mysql_real_escape_string对content字段来进行转义
        //转义再插入成功后自动转移回来
        //文档上说明转义的缓冲区长度必须是之前的2倍+1
        //使用unique_ptr管理内存
        std::unique_ptr<char> content_escape(new char[content.size()*2+1]);
        mysql_real_escape_string(mysql_,content_escape.get(),content.c_str(),content.size());
        //插入的博客内容根据用户请求的长度自适应
        std::unique_ptr<char> sql(new char[content.size()*2+4096]);
        sprintf(sql.get(),"insert into blog_table values(null,'%s','%s',%d,'%s')",
            blog["title"].asCString(),content_escape.get(),
            blog["tag_id"].asInt(),blog["create_time"].asCString());
        int ret = mysql_query(mysql_,sql.get());
        if(ret<0){
          printf("执行sql失败！sql=%s,%s\n",sql.get(),mysql_error(mysql_));
          return false;
        }
        return true;
      }

      bool SelectAll(Json::Value* blogs, const std::string& tag_id = ""){
        char sql[1024*4]={0};
        if(tag_id.empty()){
            sprintf(sql,"select blog_id,title,tag_id,create_time from blog_table");
        }else{
          sprintf(sql,"select blog_id,title,tag_id,create_time from blpg_table where tag_id = '%s'",tag_id.c_str());
        }
        int ret =mysql_query(mysql_,sql);
        if(ret != 0){
          printf("执行sql失败!%s\n",mysql_error(mysql_));
          return false;
        }
        MYSQL_RES* result = mysql_store_result(mysql_);
        if(result == NULL){
          printf("获取结果失败! %s\n",mysql_error(mysql_));
          return false;
        }
        int rows = mysql_num_rows(result);
        for(int i=0;i<rows;++i){
          MYSQL_ROW row = mysql_fetch_row(result);
          Json::Value blog;
          blog["blog_id"] = atoi(row[0]);
          blog["title"] = row[1];
          blog["tag_id"] = atoi(row[2]);
          blog["create_time"]=row[3];
          blogs->append(blog);

        }
        return true;
      }

      bool SelectOne(int32_t blog_id,Json::Value* blog){
        char sql[1024*4]={0};
        sprintf(sql,"select * from blog_table where blog_id = %d",blog_id);
        int ret = mysql_query(mysql_,sql);
        if(ret != 0){
          printf("执行sql失败! %s\n",mysql_error(mysql_));
          return false;
        }
        MYSQL_RES* result = mysql_store_result(mysql_);
        if(result == NULL){
          printf("获取结果失败！ %s\n",mysql_error(mysql_));
          return false;
        }
        int rows = mysql_num_rows(result);
        if(rows != 1){
          printf("查找结果不为1，rows=%d\n",rows);
          return false;
        }
        MYSQL_ROW row = mysql_fetch_row(result);
        (*blog)["blog_id"] = atoi(row[0]);
        (*blog)["title"] = row[1];
        (*blog)["content"] = row[2];
        (*blog)["tag_id"] = atoi(row[3]);
        (*blog)["create_time"] = row[4];
        return true;
      }

      bool Update(const Json::Value& blog){
        const std::string& content = blog["content"].asString();
        std::unique_ptr<char> content_escape(new char[content.size()*2+1]);
        mysql_real_escape_string(mysql_,content_escape.get(),content.c_str(),content.size());
        std::unique_ptr<char> sql(new char[content.size()*2 + 4096]);
        sprintf(sql.get(),"update blog_table set title='%s',content='%s',tag_id=%d where blog_id=%d",blog["title"].asCString(),content_escape.get(),blog["tag_id"].asInt(),blog["blog_id"].asInt());
        int ret =mysql_query(mysql_,sql.get());
        if(ret != 0){
          printf("执行sql失败！sql = %s,%s\n",sql.get(),mysql_error(mysql_));
          return false;
        }
        return true;
        
      }
      
      bool Delete(int blog_id){
        char sql[1024*4]={0};
        sprintf(sql,"delete from blog_table where blog_id=%d",blog_id);
        int ret =mysql_query(mysql_,sql);
        if(ret != 0){
          printf("执行sql失败! sql = %s,%s\n",sql,mysql_error(mysql_));
          return false;
        }
        return true;
      }
    private:
      MYSQL* mysql_;
  };

  class TagTable{
    public:
      TagTable(MYSQL* mysql):mysql_(mysql){}

      bool SelectAll(Json::Value* tags){
        char sql[1024*4] = {0};
        sprintf(sql,"select * from tag_table");
        int ret = mysql_query(mysql_,sql);
        if(ret != 0){
          printf("执行sql失败! %s\n",mysql_error(mysql_));
          return false;
        }
        MYSQL_RES * result = mysql_store_result(mysql_);
        if(result == NULL){
          printf("获取结果失败! %s\n",mysql_error(mysql_));
          return false;
        }
        int rows = mysql_num_rows(result);
        for(int i=0;i<rows;++i){
          MYSQL_ROW row = mysql_fetch_row(result);
          Json::Value tag;
          tag["tag_id"] = atoi(row[0]);
          tag["tag_name"]= row[1];
          tags->append(tag);
        }
        return true;
      }

      bool Insert(const Json::Value& tag){
        char sql[1024*4]={0};
        sprintf(sql,"insert into tag_table values(NULL,'%s')",tag["tag_name"].asCString());
        int ret = mysql_query(mysql_,sql);
        if(ret != 0){
          printf("执行sql失败! sql=%s,%s\n",sql,mysql_error(mysql_));
          return false;
        }
        return true;
      }

      bool Delete(int tag_id){
        char sql[1024*4] = {0};
        sprintf(sql,"delete from tag_table where tag_id=%d",tag_id);
        int ret =mysql_query(mysql_,sql);
        if(ret!=0){
          printf("执行sql失败! sql=%s,%s\n",sql,mysql_error(mysql_));
          return false;
        }
        return true;
      }
    private:
      MYSQL* mysql_;
  };
