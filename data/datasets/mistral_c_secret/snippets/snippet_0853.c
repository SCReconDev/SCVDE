#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

typedef struct {
    Aws::S3::S3Client *client;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-east-1";

    helper->client = new Aws::S3::S3Client(config);
    if (helper->client == NULL) {
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
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

    printf("Cloud storage helper created for bucket: %s\n", helper->bucket_name);

    destroy_cloud_storage_helper(helper);
    return 0;
}