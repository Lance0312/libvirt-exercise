#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

int main(int argc, char *argv[]) {
    virConnectPtr conn;
    conn = virConnectOpen("qemu:///system");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return 1;
    }

    int i;
    int numDomains;
    int *activeDomains;
    numDomains = virConnectNumOfDomains(conn);
    activeDomains = malloc(sizeof(int) * numDomains);
    numDomains = virConnectListDomains(conn, activeDomains, numDomains);
    printf("Active domain IDs:\n");
    for (i = 0 ; i < numDomains ; i++) {
        printf(" %d\n", activeDomains[i]);
    }
    free(activeDomains);

    i = 0;
    numDomains = 0;
    char **inactiveDomains;
    numDomains = virConnectNumOfDefinedDomains(conn);
    inactiveDomains = malloc(sizeof(char *) * numDomains);
    numDomains = virConnectListDefinedDomains(conn, inactiveDomains, numDomains);
    printf("Inactive domain names:\n");
    for (i = 0 ; i < numDomains ; i++) {
        printf(" %s\n", inactiveDomains[i]);
        free(inactiveDomains[i]);
    }
    free(inactiveDomains);

    virConnectClose(conn);  
    return 0;
}
