#ifdef __cplusplus
extern "C" {
#endif

int help(char **arg,char *s,...);
char *get_arg(char *str_to_find, int narg, char **arg);
int exist_arg(char *str_to_find, int narg, char **arg);

#define GET_ARG(str) get_arg(str,argc,argv)
#define EXIST_ARG(str) exist_arg(str,argc,argv)

#ifdef __cplusplus
}
#endif
