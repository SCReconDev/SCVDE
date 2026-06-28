#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

#define ACCESS_KEY_ENV_VAR "AWS_ACCESS_KEY_ID"
#define SECRET_KEY_ENV_VAR "AWS_SECRET_ACCESS_KEY"

typedef struct {
    Aws::S3::S3Client *client;
    Aws::String bucket_name;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket_name = Aws::String(bucket_name);

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    char *access_key = getenv(ACCESS_KEY_ENV_VAR);
    char *secret_key = getenv(SECRET_KEY_ENV_VAR);

    if (access_key == NULL || secret_key == NULL) {
        fprintf(stderr, "AWS credentials not found in environment variables\n");
        free(helper);
        Aws::ShutdownAPI(options);
        return NULL;
    }

    Aws::Auth::AWSCredentials credentials(access_key, secret_key);
    helper->client = new Aws::S3::S3Client(credentials, config);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
        }
        free(helper);
    }
}

void list_objects(CloudStorageHelper *helper) {
    if (helper == NULL || helper->client == NULL) {
        fprintf(stderr, "Invalid cloud storage helper\n");
        return;
    }

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket(helper->bucket_name);

    auto outcome = helper->client->ListObjects(request);
    if (outcome.IsSuccess()) {
        printf("Objects in bucket %s:\n", helper->bucket_name.c_str());
        Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();
        for (const auto &object : objects) {
            printf("%s\n", object.GetKey().c_str());
        }
    } else {
        fprintf(stderr, "Failed to list objects: %s\n", outcome.GetError().GetMessage().c_str());
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper\n");
        return 1;
    }

    list_objects(helper);
    destroy_cloud_storage_helper(helper);

    return 0;
}