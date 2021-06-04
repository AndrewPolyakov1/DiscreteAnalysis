#include "RBTree.hpp"

int main() {
    TRBTree tree; 

    char *command = (char*)calloc(260,sizeof(char)); 

    char *key = (char*)calloc(260,sizeof(char)); 
    unsigned long long value;

    if(command == NULL || command == nullptr || key == NULL || key == nullptr) {
        printf("ERROR: allocation error\n");
        return -1;
    }

    while (scanf("%s", command) != EOF) {
        if(strlen(command)>256) {
            printf("ERROR: uncorrect input\n");
            continue;
        }
        if (command[0] == '+') {
            if(scanf("%s %llu", key, &value) == EOF) {
                break;
            }
            if(strlen(key) > 256) {
                printf("ERROR: uncorrect input\n");
                continue;
            }
            int mrk = tree.Add(key, value);
            if (mrk == 0) {
                printf("OK\n");
            }
            else {
                if (mrk == -7) {
                    printf("Exist\n");
                }
                else
                if (mrk == -3) {
                    printf("ERROR: empty input\n");
                }
                else
                if (mrk == -4) {
                    printf("ERROR: untraced allocation error\n");
                }
                else
                if (mrk == -1) {
                    printf("ERROR: out of memory\n");
                }
                else {
                    printf("ERROR: unknown error\n");
                }
            }
        }
        else 
        if (command[0] == '-') {
            if(scanf("%s", key) == EOF) {
                break;
            }
            if(strlen(key)>256) {
                printf("ERROR: uncorrect input\n");
                continue;
            }
            int mrk = tree.Remove(key);
            if (mrk == 0) {
                printf("OK\n");
            }
            else 
            if (mrk == -8) {
                printf("NoSuchWord\n");
            }
            else
            if (mrk == -1) {
                printf("ERROR: out of memory\n");
            }
            else {
                printf("ERROR: unknown error\n");
            }
        }
        else
        if (command[0] == '!') {
            std::string path;
            if(scanf("%s", key) == EOF) {
                break;
            }
            if (strcmp(key, "Save") == 0) {
                std::cin >> path;
                
                int mrk = tree.Save(path); 
                if (mrk == 0) {
                    printf("OK\n");
                    continue;
                }
                else 
                if (mrk == 1) {
                    printf("OK\n");
                    continue;
                }
                else 
                if (mrk == -1) {
                    printf("ERROR: unable to open file\n");
                    continue;
                }
                else 
                if (mrk == -2) {
                    printf("ERROR: unable to write file\n");
                    continue;
                }
                else 
                if (mrk == -3) {
                    printf("ERROR: file acsess error\n");
                    continue;
                }
                else 
                {
                    printf("ERROR: something gone wrong\n");
                    continue;
                }
            }
            else
            if (strcmp(key, "Load") == 0) {
                std::cin >> path;

                int mrk = tree.Load(path); 
                if (mrk == 0) {
                    printf("OK\n");
                    continue;
                }
                else 
                if (mrk == -1) {
                    printf("ERROR: file is damaged\n");
                    continue;
                }
                else 
                if (mrk == -2) {
                    printf("ERROR: wrong format of file\n");
                    continue;
                }
                else 
                if (mrk == -3) {
                    printf("ERROR: file acsess error\n");
                    continue;
                }
                else 
                {
                    printf("ERROR: something gone wrong\n");
                    continue;
                }
            }
            
        }
        else {
            Node* res = tree.Search(command);
            if (res != nullptr) {
                printf("OK: %llu\n",res->value);
            }
            else {
                printf("NoSuchWord\n");
            }
        }
    }
    
    tree.Destroy(); 
    free(command);
    free(key);

    return 0;
}