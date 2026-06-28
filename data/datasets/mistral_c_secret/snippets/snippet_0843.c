#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>

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

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    helper->client = new Aws::S3::S3Client(config);
    if (helper->client == NULL) {
        free(helper->bucket_name);
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

int download_file(CloudStorageHelper *helper, const char *object_key, const char *file_path) {
    if (helper == NULL || object_key == NULL || file_path == NULL) {
        return -1;
    }

    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(helper->bucket_name);
    request.SetKey(object_key);

    auto outcome = helper->client->GetObject(request);
    if (!outcome.IsSuccess()) {
        fprintf(stderr, "Failed to download file: %s\n", outcome.GetError().GetMessage().c_str());
        return -1;
    }

    auto &retrieved_file = outcome.GetResultWithOwnership().GetBody();
    std::ofstream output_file(file_path, std::ios::binary);
    output_file << retrieved_file.rdbuf();

    return 0;
}

int main() {
    const char *bucket_name = getenv("S3_BUCKET_NAME");
    if (bucket_name == NULL) {
        fprintf(stderr, "S3_BUCKET_NAME environment variable not set.\n");
        return 1;
    }

    CloudStorageHelper *helper = create_cloud_storage_helper(bucket_name);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create cloud storage helper.\n");
        return 1;
    }

    if (download_file(helper, "example.txt", "downloaded_example.txt") != 0) {
        fprintf(stderr, "Failed to download file.\n");
        destroy_cloud_storage_helper(helper);
        return 1;
    }

    destroy_cloud_storage_helper(helper);

    return 0;
}