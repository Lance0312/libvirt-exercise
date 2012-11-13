#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>                                                                
#include <sys/stat.h>                                                                       

void main(int argc, char* argv[]) {                                                         
    virConnectPtr conn;                                                                 
    virNetworkPtr net;
    char* config_file;                                                                  
    FILE* xml_file;                                                                     
    char *xmlconfig;                                                                    
    struct stat st;                                                                     

    if (argc != 2) {                                                                    
        fprintf(stderr, "Usage: ./newNetwork config\n");
        return;                                                                     
    }

    config_file = argv[1];
    stat(config_file, &st);
    int file_size = st.st_size;

    xml_file = fopen(config_file, "r");
    if (xml_file == NULL) {
        fprintf(stderr, "Cannot open file\n");
    }
    xmlconfig = malloc(file_size);
    int result = fread(xmlconfig, 1, file_size, xml_file);

    conn = virConnectOpen("qemu:///system");
    if (conn == NULL) {
        fprintf(stderr, "Failed to open connection to qemu:///system\n");
        return;
    }

    net = virNetworkDefineXML(conn, xmlconfig);

    if (!net) {
        fprintf(stderr, "Network definition failed");
        return;
    }

    if (virNetworkCreate(net) < 0) {
        virNetworkFree(net);
        fprintf(stderr, "Cannot start network");
        return;
    }

    //fprintf(stderr, "Guest %s has booted", virDomainName(dom));
    virNetworkFree(net);
    virConnectClose(conn);
    free(xmlconfig);
    return;
}
