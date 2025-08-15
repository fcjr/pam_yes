#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <security/pam_modules.h>
#else
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#endif

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    char response[10];
    
    printf("Do you want to proceed with sudo? (y/N): ");
    fflush(stdout);
    
    if (fgets(response, sizeof(response), stdin) != NULL) {
        response[strcspn(response, "\n")] = 0;
        
        if (strcmp(response, "y") == 0 || 
            strcmp(response, "Y") == 0 || 
            strcmp(response, "yes") == 0) {
            return PAM_SUCCESS;
        }
    }
    
    return PAM_AUTH_ERR;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}