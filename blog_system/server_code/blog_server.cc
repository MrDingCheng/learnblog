#include <mysql/mysql.h>
#include "httplib.h"
#include "db.hpp"
MYSQL* mysql = NULL;
int main(){
  using namespace httplib;
  Server server;
  //server.Get("/",[](const Request& req, Response& resp){
  //    (void) req;
  //    resp.set_content("<html>hello</html>","text/html");
  //    });
  //server.set_base_dir("./wwwroot");
  //server.listen("0.0.0.0",9092);
  //1.数据库客户端初始化和释放
  mysql = MySQLInit();
  signal(SIGINT,[](int){
      MYSQLRelease(mysql);
      exit(0);
      });
  BlogTable blog_table(mysql);
  TagTable tag_table(mysql);

  //2.设置路由
  //新增博客
  server.Post("/blog",[&blog_table](const Request& req, Response& resp){
      printf("新增博客:%s\n",req.body.c_str());
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      //1.请求解析成Json格式
      bool ret = reader.parse(req.body,req_json);
      if(!ret){
      //请求解析出错，返回一个400响应
      resp_json["ok"] = false;
      resp_json["reason"] = "parse Request failed!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //2.进行参数校验
      if(req_json["title"].empty()||req_json["content"].empty()||req_json["tag_id"].empty()||req_json["create_time"].empty()){
      resp_json["ok"] = false;
      resp_json["reason"] = "Request failed error!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //3.调用数据库接口进行操作数据
      ret = blog_table.Insert(req_json);
      if(!ret){
        resp_json["ok"] = false;
        resp_json["reason"] = "Insert failed!\n";
        resp.status = 500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //4.封装正确的返回结果
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      });
  //查看所有博客(可以按标签筛选)
  server.Get("/blog",[&blog_table](const Request& req, Response& resp){
      printf("查看所有博客\n");
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value resp_json;
      //如果没传tag_id,返回的是空字符串
      const std::string& tag_id = req.get_param_value("tag_id");
      //对于查看博客来说API没有请求参数，不需要解析和检验参数，直接构造结果
      //1.调用数据库接口查询数据
      Json::Value blogs;
      bool ret = blog_table.SelectAll(&blogs,tag_id);
      if(!ret){
      resp_json["ok"] = false;
      resp_json["reason"] = "SelectAll failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //2.构造响应结果
      resp.set_content(writer.write(blogs),"application/json");
      return;

      });
  //查看一篇博客内容
  server.Get(R"(/blog/(\d+))",[&blog_table](const Request& req, Response& resp){
      Json::Value resp_json;
      Json::FastWriter writer;
      //1.解析获取blog_id
      int blog_id = std::stoi(req.matches[1]);
      printf("查看指定博客：%d\n",blog_id);
      //2.调用数据库接口查看博客
      bool ret = blog_table.SelectOne(blog_id,&resp_json);
      if(!ret){
      resp_json["ok"] = false;
      resp_json["reason"] = "SelectOne failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //3.封装响应
      resp_json["ok"] = true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      });
  //删除博客
  server.Delete(R"(/blog/(\d+))",[&blog_table](const Request& req, Response& resp){
      Json::Value resp_json;
      Json::FastWriter writer;
      //1.解析获取blog_id
     int blog_id = std::stoi(req.matches[1]);
     printf("删除指定博客:%d\n",blog_id);
     //2.调用数据库接口删除博客
     bool ret = blog_table.Delete(blog_id);
     if(!ret){
      resp_json["ok"] = false;
      resp_json["reason"] = "Delete failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //3.封装响应
      resp_json["ok"] = true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      });
  //修改博客
  server.Put(R"(/blog/(\d+))",[&blog_table](const Request& req, Response& resp){
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      //1.获取blog_id
      int blog_id = std::stoi(req.matches[1]);
      printf("修改博客:%d\n",blog_id);
      //2.解析博客信息
      bool ret = reader.parse(req.body, req_json);
      if(!ret){
      //请求解析出错,返回一个400响应
      resp_json["ok"] = false;
      resp_json["reason"] = "parse Request failed!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      req_json["blog_id"] = blog_id;
      //3.检验博客信息
      if(req_json["title"].empty()||req_json["content"].empty()||req_json["tag_id"].empty()){
        //请求解析出错，返回一个400响应
        resp_json["ok"] = false;
        resp_json["reason"] = "Request has no name or price!\n";
        resp.status = 400;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //4.调用数据库接口进行修改
      ret = blog_table.Update(req_json);
      if(!ret){
        resp_json["ok"] = false;
        resp_json["reason"] = "Update failed!\n";
        resp.status = 500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //5.封装正确响应
      resp_json["ok"] = true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      });
  //新增标签
  server.Post("/tag",[&tag_table](const Request& req, Response& resp){
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      //1.解析请求
      bool ret = reader.parse(req.body,req_json);
      if(!ret){
      //请求解析出错，返回一个400响应
      resp_json["ok"] = false;
      resp_json["reason"] = "parse Request failed!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json),"application/text");
      return;
      }
      //2.检验标签格式
      if(req_json["tag_name"].empty()){
      //请求解析出错，返回一个400响应
      resp_json["ok"] = false;
      resp_json["reason"] = "Request has no tag_id or tag_name!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //3.调用数据库接口，插入标签
      ret = tag_table.Insert(req_json);
      if(!ret){
        resp_json["ok"] = false;
        resp_json["reason"] = "Tag Insert failed!\n";
        resp.status = 500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //4.封装正确请求
      resp_json["ok"] = true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;

      });
  //删除标签
  server.Delete(R"(/tag/(\d+))",[&tag_table](const Request& req, Response& resp){
      Json::Value resp_json;
      Json::FastWriter writer;
      //1.获取tag_id
      int tag_id = std::stoi(req.matches[1]);
      printf("删除指定标签tag_id = %d\n",tag_id);
      //2.执行数据库操作删除标签
      bool ret = tag_table.Delete(tag_id);
      if(!ret){
        resp_json["ok"] = false;
        resp_json["reason"] = "Tag Delete failed!\n";
        resp.status = 500;
        resp.set_content(writer.write(resp_json),"application/json");
        return;
      }
      //3.封装正确响应
      resp_json["ok"] = true;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      });
  //获取所有标签
  server.Get("/tag",[&tag_table](const Request& req, Response& resp){
      (void) req;
      printf("查看所有标签！\n");
      Json::FastWriter writer;
      Json::Value resp_json;
      //1.调用数据库接口查询
      Json::Value tags;
      bool ret = tag_table.SelectAll(&tags);
      if(!ret){
      resp_json["ok"] = false;
      resp_json["reason"] = "SelectAll Tags failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json),"application/json");
      return;
      }
      //2.构造响应结果
      resp.set_content(writer.write(tags),"application/json");
      return;
      });
 //设置静态文件目录

  server.set_base_dir("./wwwroot");
  server.listen("0.0.0.0",9093);

  return 0;
}
