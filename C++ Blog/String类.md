# String类

### string类对象的常见构造

string（）；//构造空的string类对象，即空字符串

### string类对象的修改操作

void push_back(char c);//在字符串末尾插字符c

string& append（const char* s）；//在字符串后追加一个字符串

string& operator+=（const string& str）；//在字符串后追加字符串str

string& operator+=（const char* s）；//在字符串后追加字符串s

string& operator+=（char c）；//在字符串后追加字符c

const char* c_str() const；//返回C格式字符串

string& insert（size_t pos,  const string& str）;//从pos位置插入str

string& erase（size_t pos = 0，size_t len = npos）;//从pos开始删除len个字符，无参则全删

string& replace（size_t pos, size_t len, const string& str）;//把原字符串的pos后的len个字符替换为str

size_t find(char c, size_t pos =0 ) const ;//从字符串pos位置开始往后查找字符c,返回字符c在字符串中的的位置

size_t rfind(char c, size_t pos = npos) const;//从字符串从字符串pos位置开始往前查找字符c,返回字符c在字符串中的的位置