#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>

#define AWS_ACCESS_KEY_ID_ENV_VAR "AWS_ACCESS_KEY_ID"
#define AWS_SECRET_ACCESS_KEY_ENV_VAR "AWS_SECRET_ACCESS_KEY"

typedef struct {
    Aws::S3::S3Client *s3_client;
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

    const char *access_key_id = getenv(AWS_ACCESS_KEY_ID_ENV_VAR);
    const char *secret_access_key = getenv(AWS_SECRET_ACCESS_KEY_ENV_VAR);

    if (access_key_id == NULL || secret_access_key == NULL) {
        fprintf(stderr, "AWS credentials not found in environment variables\n");
        free(helper->bucket_name);
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    Aws::Auth::AWSCredentials credentials(access_key_id, secret_access_key);
    helper->s3_client = new Aws::S3::S3Client(credentials, config);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->s3_client != NULL) {
            delete helper->s3_client;
        }
        if (helper->bucket_name != NULL) {
            free(helper->bucket_name);
        }
        free(helper);
    }
}

int main() {
    const char *bucket_name = "my-bucket";

    CloudStorageHelper *helper = create_cloud_storage_helper(bucket_name);

    if (helper != NULL) {
        printf("Cloud storage helper created successfully\n");
        destroy_cloud_storage_helper(helper);
    } else {
        fprintf(stderr, "Failed to create cloud storage helper\n");
    }

    Aws::ShutdownAPI();

    return 0;
}