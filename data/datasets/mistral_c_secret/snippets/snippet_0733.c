#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>

#define BUCKET_NAME "example-bucket"

typedef struct {
    Aws::S3::S3Client *client;
    char *access_key;
} CloudStorageHelper;

CloudStorageHelper *create_cloud_storage_helper(const char *access_key) {
    CloudStorageHelper *helper = (CloudStorageHelper *)malloc(sizeof(CloudStorageHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->access_key = strdup(access_key);
    if (helper->access_key == NULL) {
        free(helper);
        return NULL;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    helper->client = new Aws::S3::S3Client(config);

    return helper;
}

void destroy_cloud_storage_helper(CloudStorageHelper *helper) {
    if (helper != NULL) {
        if (helper->client != NULL) {
            delete helper->client;
        }
        free(helper->access_key);
        free(helper);

        Aws::SDKOptions options;
        Aws::ShutdownAPI(options);
    }
}

int download_file(CloudStorageHelper *helper, const char *key, const char *file_path) {
    if (helper == NULL || key == NULL || file_path == NULL) {
        return -1;
    }

    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(BUCKET_NAME);
    request.SetKey(key);

    auto outcome = helper->client->GetObject(request);
    if (!outcome.IsSuccess()) {
        fprintf(stderr, "Failed to download file: %s\n", outcome.GetError().GetMessage().c_str());
        return -1;
    }

    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing.\n");
        return -1;
    }

    auto &retrieved_file = outcome.GetResultWithOwnership().GetBody();
    char buffer[1024];
    while (retrieved_file.good()) {
        retrieved_file.read(buffer, sizeof(buffer));
        fwrite(buffer, 1, retrieved_file.gcount(), file);
    }

    fclose(file);

    printf("Successfully downloaded file: %s\n", key);

    return 0;
}

int main() {
    const char *access_key = getenv("AWS_ACCESS_KEY");
    if (access_key == NULL) {
        fprintf(stderr, "AWS_ACCESS_KEY environment variable not set.\n");
        return 1;
    }

    CloudStorageHelper *helper = create_cloud_storage_helper(access_key);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper.\n");
        return 1;
    }

    if (download_file(helper, "example.txt", "downloaded_example.txt") != 0) {
        destroy_cloud_storage_helper(helper);
        return 1;
    }

    destroy_cloud_storage_helper(helper);

    return 0;
}