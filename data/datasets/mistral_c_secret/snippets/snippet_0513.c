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

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration client_config;
    client_config.region = Aws::Region::US_EAST_1;

    const char *access_key = getenv("AWS_ACCESS_KEY_ID");
    const char *secret_key = getenv("AWS_SECRET_ACCESS_KEY");
    if (access_key == NULL || secret_key == NULL) {
        fprintf(stderr, "AWS_ACCESS_KEY_ID or AWS_SECRET_ACCESS_KEY environment variable not set.\n");
        free(helper->bucket_name);
        free(helper);
        Aws::ShutdownAPI(options);
        return NULL;
    }

    Aws::Auth::AWSCredentials credentials(access_key, secret_key);
    helper->client = new Aws::S3::S3Client(credentials, client_config);

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
        Aws::SDKOptions options;
        Aws::ShutdownAPI(options);
    }
}

int list_objects(CloudStorageHelper *helper, const char *prefix, Aws::Vector<Aws::S3::Model::Object> *objects) {
    if (helper == NULL || prefix == NULL || objects == NULL) {
        return -1;
    }

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket(helper->bucket_name);
    request.SetPrefix(prefix);

    auto outcome = helper->client->ListObjects(request);
    if (!outcome.IsSuccess()) {
        fprintf(stderr, "ListObjects error: %s\n", outcome.GetError().GetMessage().c_str());
        return -1;
    }

    *objects = outcome.GetResult().GetContents();
    return 0;
}