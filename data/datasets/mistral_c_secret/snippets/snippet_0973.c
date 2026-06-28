#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>

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

    const char *access_key = getenv(ACCESS_KEY_ENV_VAR);
    const char *secret_key = getenv(SECRET_KEY_ENV_VAR);

    if (access_key == NULL || secret_key == NULL) {
        fprintf(stderr, "Error: AWS credentials not found in environment variables.\n");
        free(helper);
        Aws::ShutdownAPI(options);
        return NULL;
    }

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

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
        Aws::SDKOptions options;
        Aws::ShutdownAPI(options);
    }
}

int main() {
    CloudStorageHelper *helper = create_cloud_storage_helper("my-bucket");
    if (helper == NULL) {
        return EXIT_FAILURE;
    }

    printf("Cloud storage helper created for bucket: %s\n", helper->bucket_name.c_str());

    destroy_cloud_storage_helper(helper);
    return EXIT_SUCCESS;
}