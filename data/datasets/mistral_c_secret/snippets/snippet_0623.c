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

CloudStorageHelper* create_cloud_storage_helper(const char *access_key, const char *secret_key, const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    Aws::Auth::AWSCredentials credentials(access_key, secret_key);
    helper->client = new Aws::S3::S3Client(credentials, config);

    helper->bucket_name = strdup(bucket_name);
    if (helper->bucket_name == NULL) {
        delete helper->client;
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
        free(helper->bucket_name);
        free(helper);
    }
}

int list_objects(CloudStorageHelper *helper) {
    if (helper == NULL || helper->client == NULL || helper->bucket_name == NULL) {
        return -1;
    }

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket(helper->bucket_name);

    auto outcome = helper->client->ListObjects(request);
    if (!outcome.IsSuccess()) {
        fprintf(stderr, "Failed to list objects: %s\n", outcome.GetError().GetMessage().c_str());
        return -1;
    }

    auto objects = outcome.GetResult().GetContents();
    for (const auto &object : objects) {
        printf("Object: %s\n", object.GetKey().c_str());
    }

    return 0;
}

int main() {
    const char *access_key = getenv("AWS_ACCESS_KEY");
    const char *secret_key = getenv("AWS_SECRET_KEY");
    const char *bucket_name = getenv("AWS_BUCKET_NAME");

    if (access_key == NULL || secret_key == NULL || bucket_name == NULL) {
        fprintf(stderr, "AWS environment variables not set\n");
        return 1;
    }

    CloudStorageHelper *helper = create_cloud_storage_helper(access_key, secret_key, bucket_name);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    if (list_objects(helper) != 0) {
        fprintf(stderr, "Failed to list objects\n");
        destroy_cloud_storage_helper(helper);
        return 1;
    }

    destroy_cloud_storage_helper(helper);
    return 0;
}