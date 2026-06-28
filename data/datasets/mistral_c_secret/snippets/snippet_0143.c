#include <stdio.h>
#include <stdlib.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

#define ACCESS_KEY "fake_access_key_1234567890"
#define SECRET_KEY "fake_secret_key_1234567890"

void list_s3_objects() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "us-west-2";

    Aws::Auth::AWSCredentials credentials(ACCESS_KEY, SECRET_KEY);
    Aws::S3::S3Client s3_client(credentials, clientConfig);

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket("example-bucket");

    auto outcome = s3_client.ListObjects(request);
    if (outcome.IsSuccess()) {
        printf("Listed objects successfully\n");
    } else {
        printf("Error: %s\n", outcome.GetError().GetMessage().c_str());
    }

    Aws::ShutdownAPI(options);
}

int main() {
    list_s3_objects();
    return 0;
}