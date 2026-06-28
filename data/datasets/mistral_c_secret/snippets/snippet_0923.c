#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>

int main(void) {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::String access_key = Aws::Environment::GetEnv("AWS_ACCESS_KEY_ID");
    Aws::String secret_key = Aws::Environment::GetEnv("AWS_SECRET_ACCESS_KEY");

    if (access_key.empty() || secret_key.empty()) {
        fprintf(stderr, "AWS_ACCESS_KEY_ID or AWS_SECRET_ACCESS_KEY environment variable not set\n");
        Aws::ShutdownAPI(options);
        return 1;
    }

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    Aws::Auth::AWSCredentials credentials(access_key, secret_key);
    Aws::S3::S3Client s3_client(credentials, config);

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket("example-bucket");

    auto outcome = s3_client.ListObjects(request);
    if (outcome.IsSuccess()) {
        Aws::S3::Model::ListObjectsResult result = outcome.GetResult();
        for (auto const &object : result.GetContents()) {
            std::cout << object.GetKey() << std::endl;
        }
    } else {
        std::cerr << "Error: " << outcome.GetError().GetMessage() << std::endl;
    }

    Aws::ShutdownAPI(options);

    return 0;
}