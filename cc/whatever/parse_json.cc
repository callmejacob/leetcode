/**
    parse given json
    {
        "key1": "value1",
        "key2": {
            "key21": "value21",
            "key22": "value22"
        }
    }
*/

#include <iostream>
#include <string>
#include <list>

using namespace std;

/*********************************************************/
/*******************   结构定义   *************************/
/*********************************************************/
class json_object;

// 类型基类，包含key键
class base_item {
public:
    base_item(string key) : key_(key) {}
    virtual ~base_item() {}

public:
    virtual void print() = 0;     

protected:
     string key_;    
};

// 字符串子项，value类型为string
class string_item : public base_item {
public:
    string_item(string key, string value) 
            : base_item(key), value_(value) {}
    virtual ~string_item() {}

public:
    void print();

private:
    string value_;    
};

// 对象子项，value类型为object
class object_item : public base_item {
public:
    object_item(string key, shared_ptr<json_object> value)
            : base_item(key), value_(value) {}
    virtual ~object_item() {}

public:
    void print();

private: 
    shared_ptr<json_object> value_;
};

// json对象，包含子项列表
class json_object {
public:
    json_object() {}
    virtual ~json_object() {}    

public:
    void add(shared_ptr<base_item> item) {
        list_.push_back(item);
    }

    void print();

private: 
    list<shared_ptr<base_item>> list_;
};

// 打印方法
void string_item::print() {
    cout << "string item ---> {";
    cout << "key:" << key_ << " value:" << value_;
    cout << "}" << endl;
}    

void object_item::print() {
    cout << "object item ---> {" << endl;
    cout << "key:" << key_ << " {" << endl;
    value_->print();
    cout << '}' << endl;
}

void json_object::print() {
    for (auto iter = list_.cbegin(); iter != list_.cend(); iter++) {
        (*iter)->print();
    }
}

/*********************************************************/
/*******************   json解析   ************************/
/*********************************************************/
// 状态定义
const int STATE_INIT            = 0;
const int STATE_OBJECT          = 1;
const int STATE_KEY             = 2;
const int STATE_KEY_DONE        = 3;
const int STATE_VALUE           = 4;
const int STATE_VALUE_DONE      = 5;

shared_ptr<json_object> parse_json_object(const char*& p);

// 解析字符串子项
shared_ptr<string_item> parse_string_item(const char*& p, string& key) {
    string value;
    while (*p) {
        switch (*p) {
        case '"': {
            return make_shared<string_item>(key, value);
        }
        default:
            value.append(p, 1);
            break;            
        }
        ++p;
    }
    return nullptr;
}

// 解析对象子项
shared_ptr<object_item> parse_object_item(const char*& p, string& key) {
    shared_ptr<json_object> object = parse_json_object(p);
    if (object != nullptr) {
        return make_shared<object_item>(key, object);
    }
    return nullptr;
}

// 解析json对象，状态机轮转
shared_ptr<json_object> parse_json_object(const char*& p) {
    shared_ptr<json_object> result = nullptr;

    int state = STATE_OBJECT;
    string key;
    while (*p) {
        if (state == STATE_OBJECT) {
            switch (*p) {
            case ' ':
                break;
            case '{':
                result = make_shared<json_object>();
                break;
            case '}':
                return result;
            case '"':
                if (result == nullptr) {
                    return nullptr;
                }
                state = STATE_KEY;
                key = "";
                break;
            default:
                break;
            }
        } else if (state == STATE_KEY) {
            switch (*p) {
            case '"':
                state = STATE_KEY_DONE;
                break;
            default:
                key.append(p, 1);
                break;
            }
        } else if (state == STATE_KEY_DONE) {
            switch (*p) {
            case ' ':
                break;
            case ':':
                state = STATE_VALUE;
                break;
            case '}':
                state = STATE_OBJECT;
                --p;
                break;
            default:
                return nullptr;
            }
        } else if (state == STATE_VALUE) {
            switch (*p) {
            case ' ':
                break;
            case '"': {
                ++p;
                shared_ptr<string_item> item = parse_string_item(p, key);
                if (item == nullptr) return nullptr;
                result->add(item);
                state = STATE_VALUE_DONE;
                break;
            }
            case '{': {
                shared_ptr<object_item> item = parse_object_item(p, key);
                if (item == nullptr) return nullptr;
                result->add((shared_ptr<base_item>)item);
                state = STATE_VALUE_DONE;
                break;
            }
            default:
                return nullptr;
            }
        } else if (state == STATE_VALUE_DONE) {
            switch (*p) {
            case ' ':
            case ',':
                break;
            case '}':
                state = STATE_OBJECT;
                --p;
                break;
            case '"':
                state = STATE_KEY;
                key = "";
                break;
            default:
                return nullptr;
            }
        }
        ++p;
    }
    return result;
}

/*
// test
int main(int argc, char** argv) {
    string json_str = "    {"
        "\"key1\": \"value1\","
        "\"key2\": {"
        "    \"key21\": \"value21\", "
        "    \"key22\": \"value22\""
        "}"
    "}";

    const char* p = json_str.c_str();

    auto json_object = parse_json_object(p);
    if (json_object != nullptr) {
        json_object->print();
    }

    return 0;
}
*/
