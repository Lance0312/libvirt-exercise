#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>                                                                
#include <sys/stat.h>                                                                       

void main(int argc, char* argv[]) {                                                         
    virConnectPtr conn;                                                                 
    virDomainPtr dom;                                                                   
    char* config_file;                                                                  
    FILE* xml_file;                                                                     
    char *xmlconfig;                                                                    
    struct stat st;                                                                     

    if (argc != 2) {                                                                    
        fprintf(stderr, "Usage: ./newInstance config\n");                           
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

    dom = virDomainDefineXML(conn, xmlconfig);

    if (!dom) {
        fprintf(stderr, "Domain definition failed");
        return;
    }

    if (virDomainCreate(dom) < 0) {
        virDomainFree(dom);
        fprintf(stderr, "Cannot boot guest");
        return;
    }

    //fprintf(stderr, "Guest %s has booted", virDomainName(dom));
    virDomainFree(dom);
    virConnectClose(conn);
    free(xmlconfig);
    return;
}
