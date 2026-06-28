#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

typedef struct {
    char *access_key;
    char *secret_key;
    char *region;
    Aws::S3::S3Client *client;
} CloudStorageHelper;

CloudStorageHelper* create_cloud_storage_helper() {
    CloudStorageHelper *helper = (CloudStorageHelper*)malloc(sizeof(CloudStorageHelper));
    helper->access_key = getenv("AWS_ACCESS_KEY");
    helper->secret_key = getenv("AWS_SECRET_KEY");
    helper->region = getenv("AWS_REGION");

    if (helper->access_key == NULL || helper->secret_key == NULL || helper->region == NULL) {
        fprintf(stderr, "AWS_ACCESS_KEY, AWS_SECRET_KEY, and AWS_REGION environment variables must be set.\n");
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = helper->region;
    config.accessKey = helper->access_key;
    config.secretKey = helper->secret_key;

    helper->client = new Aws::S3::S3Client(config);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
        }
        Aws::ShutdownAPI(options);
        free(helper);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper();
    if (helper == NULL) {
        return EXIT_FAILURE;
    }

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket("my-bucket");

    auto outcome = helper->client->ListObjects(request);
    if (outcome.IsSuccess()) {
        printf("Listed objects in bucket: my-bucket\n");
    } else {
        fprintf(stderr, "Error listing objects: %s\n", outcome.GetError().GetMessage().c_str());
    }

    destroy_cloud_storage_helper(helper);
    return EXIT_SUCCESS;
}