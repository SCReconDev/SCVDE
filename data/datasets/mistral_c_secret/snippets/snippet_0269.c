#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OAUTH_SECRET "fake_oauth_client_secret_1234567890"

typedef struct {
    char *service;
    char *secret;
} ServiceClass;

ServiceClass* create_service(const char *service) {
    ServiceClass *sc = (ServiceClass*)malloc(sizeof(ServiceClass));
    sc->service = strdup(service);
    sc->secret = strdup(OAUTH_SECRET);
    return sc;
}

void destroy_service(ServiceClass *sc) {
    free(sc->service);
    free(sc->secret);
    free(sc);
}

void authenticate(ServiceClass *sc, const char *user) {
    printf("Authenticating user %s with service %s and OAuth client secret %s\n",
           user, sc->service, sc->secret);
}

int main() {
    ServiceClass *sc = create_service("auth-service");
    authenticate(sc, "test_user");
    destroy_service(sc);
    return 0;
}