#include <stdio.h>
#include <stdlib.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

#define ACCESS_KEY "AKIAEXAMPLE1234567890"
#define SECRET_KEY "wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY"

void list_s3_objects() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    Aws::Auth::AWSCredentials credentials(ACCESS_KEY, SECRET_KEY);
    Aws::S3::S3Client s3_client(credentials, config);

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket("example-bucket");

    auto outcome = s3_client.ListObjects(request);
    if (outcome.IsSuccess()) {
        printf("Listed objects in bucket\n");
    } else {
        printf("Error: %s\n", outcome.GetError().GetMessage().c_str());
    }

    Aws::ShutdownAPI(options);
}

int main() {
    list_s3_objects();
    return 0;
}