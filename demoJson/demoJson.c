#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <stdlib.h>

int main()
{
    #if 0
    {"way" : 1, "name" : "zhangsan", "passwd" : "abc123"}
    #endif

    /* 新建json对象 */
    struct json_object * jsonObj = json_object_new_object();
    if (jsonObj == NULL)
    {
        perror("new json object error");
        exit(-1);
    }

    struct json_object * nameValue = json_object_new_string("runoob");
    if (nameValue == NULL)
    {
        perror("new nameValue object error");
        exit(-1);
    }
    json_object_object_add(jsonObj, "name", nameValue);

    struct json_object * alexaValue = json_object_new_int64(10000);
    if (alexaValue == NULL)
    {
        perror("new alexaValue object error");
        // json_object_put(jsonObj);
        exit(-1);
    }
    int ret = json_object_object_add(jsonObj, "way", alexaValue);
    if (ret < 0)
    {
        /* todo... */
    }

    struct json_object * shoppingValue = json_object_new_array();
    if (shoppingValue == NULL)
    {
        perror("new shoppingValue object error");
        // json_object_put(jsonObj);
        exit(-1);
    }
    json_object_array_add(shoppingValue, json_object_new_string("jingdong"));
    json_object_array_add(shoppingValue, json_object_new_string("pingduoduo"));
    json_object_array_add(shoppingValue, json_object_new_string("taobao"));
    json_object_object_add(jsonObj, "shopping", shoppingValue);
    

    struct json_object * sitesValue = json_object_new_object();
    if (sitesValue == NULL)
    {
        perror("new sitesValue object error");
        // json_object_put(jsonObj);
        exit(-1);
    }
    struct json_object * site1Value = json_object_new_string("www.runoob.com");
    if (site1Value == NULL)
    {
        perror("new site1Value object error");
        exit(-1);
    }
    json_object_object_add(sitesValue, "site1", site1Value);
    struct json_object * site2Value = json_object_new_string("m.runoob.com");
    if (site2Value == NULL)
    {
        perror("new site2Value object error");
        exit(-1);
    }
    json_object_object_add(sitesValue, "site2", site2Value);
    json_object_object_add(jsonObj, "sites", sitesValue);


    /* 将json转换成字符串 */
    const char * str = json_object_to_json_string(jsonObj);
    printf("str:%s\n", str);


    /* 释放json对象 */
    json_object_put(jsonObj);
    return 0;
}
