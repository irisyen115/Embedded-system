using namespace std;
string s = "hello world!";
string sn = "123.45";

void setup() {
  Serial.begin(115200);
  Serial.printf("字串長度:%d\n", s.length() );
  string txt = s.substr(7, 2);
  Serial.printf("取出子字串:%s\n", txt.c_str() );
  s.insert(6, "new ");
  Serial.printf("插入字串之後:%s\n", s.c_str() );
  s.erase(6, 4);
  Serial.printf("刪除一段字串之後:%s\n", s.c_str() );
  s.replace(0, 6, "cyber");
  Serial.printf("替換字串之後:%s\n", s.c_str() );
  int n = s.find("world");
  Serial.printf("'world' 的起始位置:%d\n", n);
  n = s.find("@");
  if (n == string::npos) {
    Serial.println("找不到 '@' ");
  } else {
    Serial.printf("'@' 的位置:%d\n", n);
  }
  n = atoi(sn.c_str() );
  Serial.printf("sn 轉成整數:%d\n", n);
  float f = atof(sn.c_str() );
  Serial.printf("sn 轉成浮點數:%f\n", f);
}

void loop() {}