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
	int numNetworks;
	char **networkNames;
	numNetworks = virConnectNumOfNetworks(conn);
	networkNames = malloc(numNetworks * sizeof(char*));
	numNetworks = virConnectListNetworks(conn, networkNames, numNetworks);
	printf("Active networks:\n");
	for (i = 0; i < numNetworks; i++) {
	    printf(" %s\n", networkNames[i]);
	    free(networkNames[i]);
	}
	free(networkNames);

	i = 0;
	numNetworks = 0;
	numNetworks = virConnectNumOfDefinedNetworks(conn);
	networkNames = malloc(numNetworks * sizeof(char*));
	numNetworks = virConnectListDefinedNetworks(conn, networkNames, numNetworks);

	printf("Inactive networks:\n");
	for (i = 0; i < numNetworks; i++) {
	    printf(" %s\n", networkNames[i]);
	    free(networkNames[i]);
	}
	free(networkNames);

	virConnectClose(conn);  
	return 0;
}
