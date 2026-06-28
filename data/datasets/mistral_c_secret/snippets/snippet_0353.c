#include <stdio.h>
#include <stdlib.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>

#define ACCESS_KEY "fake_access_key_1234567890"
#define SECRET_KEY "fake_secret_key_1234567890"

void upload_to_s3(const char* bucket, const char* key, const char* file_path) {
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::Client::ClientConfiguration config;
    config.region = "us-west-2";

    Aws::Auth::AWSCredentials credentials(ACCESS_KEY, SECRET_KEY);
    Aws::S3::S3Client s3_client(credentials, config);

    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucket);
    request.SetKey(key);

    auto input_data = Aws::MakeShared<Aws::FStream>("PutObjectInputStream", file_path, std::ios_base::in | std::ios_base::binary);
    request.SetBody(input_data);

    auto outcome = s3_client.PutObject(request);
    if (outcome.IsSuccess()) {
        printf("Successfully uploaded %s to %s/%s\n", file_path, bucket, key);
    } else {
        printf("Error uploading %s: %s\n", file_path, outcome.GetError().GetMessage().c_str());
    }

    Aws::ShutdownAPI(options);
}

int main() {
    upload_to_s3("my-bucket", "my-key", "my-file.txt");
    return 0;
}