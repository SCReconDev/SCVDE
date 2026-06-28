#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

#define S3_BUCKET_ENV "S3_BUCKET"
#define AWS_ACCESS_KEY_ENV "AWS_ACCESS_KEY_ID"
#define AWS_SECRET_KEY_ENV "AWS_SECRET_ACCESS_KEY"

typedef struct {
    Aws::S3::S3Client *client;
    char *bucket;
} S3Helper;

S3Helper *create_s3_helper() {
    S3Helper *helper = (S3Helper *)malloc(sizeof(S3Helper));
    if (helper == NULL) {
        return NULL;
    }

    helper->bucket = getenv(S3_BUCKET_ENV);
    if (helper->bucket == NULL) {
        fprintf(stderr, "S3 bucket not found in environment variables.\n");
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-east-1";

    helper->client = new Aws::S3::S3Client(config);
    if (helper->client == NULL) {
        fprintf(stderr, "Failed to create S3 client.\n");
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_s3_helper(S3Helper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
        }
        free(helper);
    }
}

int main() {
    S3Helper *helper = create_s3_helper();
    if (helper == NULL) {
        fprintf(stderr, "Failed to create S3 helper.\n");
        return 1;
    }

    printf("S3 helper created successfully.\n");
    printf("Bucket: %s\n", helper->bucket);

    destroy_s3_helper(helper);
    return 0;
}