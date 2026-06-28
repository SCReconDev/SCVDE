#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

typedef struct {
    Aws::S3::S3Client *client;
    Aws::String bucket_name;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    char *access_key = getenv("AWS_ACCESS_KEY_ID");
    if (access_key == NULL) {
        fprintf(stderr, "AWS_ACCESS_KEY_ID environment variable not set\n");
        free(helper);
        return NULL;
    }

    char *secret_key = getenv("AWS_SECRET_ACCESS_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "AWS_SECRET_ACCESS_KEY environment variable not set\n");
        free(helper);
        return NULL;
    }

    char *region = getenv("AWS_REGION");
    if (region == NULL) {
        fprintf(stderr, "AWS_REGION environment variable not set\n");
        free(helper);
        return NULL;
    }

    char *bucket = getenv("AWS_BUCKET_NAME");
    if (bucket == NULL) {
        fprintf(stderr, "AWS_BUCKET_NAME environment variable not set\n");
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = region;

    Aws::Auth::AWSCredentials credentials(access_key, secret_key);
    helper->client = new Aws::S3::S3Client(credentials, config);
    helper->bucket_name = bucket;

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
        }
        Aws::ShutdownAPI();
        free(helper);
    }
}

int list_objects(CloudStorageHelper *helper, char *result_buffer, size_t buffer_size) {
    if (helper == NULL || result_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket(helper->bucket_name);

    auto outcome = helper->client->ListObjects(request);
    if (!outcome.IsSuccess()) {
        fprintf(stderr, "Failed to list objects: %s\n", outcome.GetError().GetMessage().c_str());
        return -1;
    }

    Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();
    for (const auto &object : objects) {
        snprintf(result_buffer, buffer_size, "%s", object.GetKey().c_str());
        break;
    }

    return 0;
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return 1;
    }

    char result[1024];
    if (list_objects(helper, result, 1024) != 0) {
        fprintf(stderr, "Failed to list objects\n");
        destroy_cloud_storage_helper(helper);
        return 1;
    }

    printf("Object Key: %s\n", result);

    destroy_cloud_storage_helper(helper);
    return 0;
}