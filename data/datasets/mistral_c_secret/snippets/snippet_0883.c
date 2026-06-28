#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

typedef struct {
    Aws::S3::S3Client *s3_client;
    char *bucket_name;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper(const char *bucket_name) {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }
    helper->bucket_name = strdup(bucket_name);

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    helper->s3_client = new Aws::S3::S3Client(config);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        delete helper->s3_client;
        free(helper->bucket_name);
        free(helper);
        Aws::ShutdownAPI(options);
    }
}

int list_objects(CloudStorageHelper *helper) {
    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket(helper->bucket_name);

    auto outcome = helper->s3_client->ListObjects(request);
    if (!outcome.IsSuccess()) {
        fprintf(stderr, "ListObjects error: %s\n", outcome.GetError().GetMessage().c_str());
        return 1;
    }

    Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();
    for (const auto &object : objects) {
        printf("Object: %s\n", object.GetKey().c_str());
    }

    return 0;
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        return 1;
    }

    list_objects(helper);

    destroy_cloud_storage_helper(helper);
    return 0;
}