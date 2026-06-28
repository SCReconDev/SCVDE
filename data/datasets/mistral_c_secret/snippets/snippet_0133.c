#include <stdio.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

#define ACCESS_KEY "fake_access_key_1234567890"
#define SECRET_KEY "fake_secret_key_1234567890"

int main() {
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
        Aws::S3::Model::ListObjectsResult result = outcome.GetResult();
        for (auto& object : result.GetContents()) {
            printf("%s\n", object.GetKey().c_str());
        }
    } else {
        printf("Error: %s\n", outcome.GetError().GetMessage().c_str());
    }

    Aws::ShutdownAPI(options);
    return 0;
}