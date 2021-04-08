/*******************************************************************************
 * Copyright (c) 2012, 2020 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *   https://www.eclipse.org/legal/epl-2.0/
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"

#define ADDRESS     "172.17.0.1:1883"//mqtt.ctwing.cn
#define CLIENTID    "1501626420201209001"
//查询模型名称信息
//#define TOPIC1       "app1-arm/get/request/database/modelschema"
//#define TOPIC2       "database/get/response/app1-arm/modelschema"
//#define PAYLOAD     "{\"token\": \"123\",\"timestamp\": \"2019-03-01T09:30:08.230+0800\",\"body\":[]}"

//查询模型内容信息
//#define TOPIC1       "app1-arm/get/request/database/model"
//#define TOPIC2       "database/get/response/app1-arm/model"
//#define PAYLOAD     "{\"token\": \"123\",\"timestamp\": \"2019-03-01T09:30:08.230+0800\",\"body\": [\"ADC\",\"ADC_frozen\",\"IEC104\",\"ZXtTmp\"]}"

//设备GUID查询
//#define TOPIC1       "app1-arm/get/request/database/guid"
//#define TOPIC2       "database/get/response/app1-arm/guid"
//#define PAYLOAD     "{\"token\": \"234\",\"timestamp\": \"2021-04-61T17:42:08.230+0800\",\"body\":[{\"model\":\"ADC\"}]}"//,\"port\":\"\",\"addr\":\"\",\"desc\":\"\"
//注册关系查询
#define TOPIC1       "app1-arm/get/request/database/register"
#define TOPIC2       "database/get/response/app1-arm/register"
#define PAYLOAD     "{\"token\": \"234\",\"timestamp\": \"2021-04-61T17:42:08.230+0800\",\"body\":[]}"

#define QOS         1
#define TIMEOUT     10000L

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

int main(int argc, char* argv[])
{
    MQTTClient client;
    //char *username= "macian"; //添加的用户名
    //char *password = "2QJgNUk11rQcAO6vz7teNqbasoNOPImhArn5DsAqKg0"; //添加的密码
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;
    printf("create mqtt client\n");

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to create client, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto exit;
    }

    if ((rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }


    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    //conn_opts.username = username; //将用户名写入连接选项中
    //conn_opts.password = password; //将密码写入连接选项中
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }

    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = (int)strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    if ((rc = MQTTClient_publishMessage(client, TOPIC1, &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }

    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC1, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
  

    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC2, CLIENTID, QOS);
    if ((rc = MQTTClient_subscribe(client, TOPIC2, QOS)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to subscribe, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }
    else
    {
    	int ch;
    	do
    	{
        	ch = getchar();
    	} while (ch!='Q' && ch != 'q');

        if ((rc = MQTTClient_unsubscribe(client, TOPIC2)) != MQTTCLIENT_SUCCESS)
        {
        	printf("Failed to unsubscribe, return code %d\n", rc);
        	rc = EXIT_FAILURE;
        }
    }

    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to disconnect, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }


destroy_exit:
    MQTTClient_destroy(&client);
exit:
    return rc;
}
