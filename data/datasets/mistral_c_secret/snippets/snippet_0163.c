#include <stdio.h>
#include <stdlib.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>

#define ACCESS_KEY "fake_access_key_ABCDEFGHIJKLMNOP"

int main() {
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
        printf("Error: %s\n", outcome.GetError().GetMessage().c_str());
    }

    Aws::ShutdownAPI(options);
    return 0;
}