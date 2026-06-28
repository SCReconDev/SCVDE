#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

#define ACCESS_KEY "AKIAIOSFODNN7EXAMPLE"

void list_s3_objects() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    Aws::S3::S3Client s3_client(config);

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket("example-bucket");

    auto outcome = s3_client.ListObjects(request);

    if (outcome.IsSuccess()) {
        printf("Listed objects in bucket\n");
    } else {
        fprintf(stderr, "Error listing objects: %s\n", outcome.GetError().GetMessage().c_str());
    }

    Aws::ShutdownAPI(options);
}

int main() {
    list_s3_objects();
    return 0;
}