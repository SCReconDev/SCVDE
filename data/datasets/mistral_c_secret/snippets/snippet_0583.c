#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>

typedef struct {
    Aws::S3::S3Client *client;
    char *bucket_name;
    char *access_key;
    char *secret_key;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        free(helper);
        return NULL;
    }

    helper->access_key = getenv("AWS_ACCESS_KEY_ID");
    if (helper->access_key == NULL) {
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    helper->secret_key = getenv("AWS_SECRET_ACCESS_KEY");
    if (helper->secret_key == NULL) {
        free(helper->access_key);
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    helper->client = new Aws::S3::S3Client(config);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
        }
        if (helper->secret_key != NULL) {
            free(helper->secret_key);
        }
        if (helper->access_key != NULL) {
            free(helper->access_key);
        }
        if (helper->bucket_name != NULL) {
            free(helper->bucket_name);
        }
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    printf("Cloud storage helper created with bucket name: %s\n", helper->bucket_name);
    printf("Cloud storage helper created with access key: %s\n", helper->access_key);

    destroy_cloud_storage_helper(helper);
    return 0;
}