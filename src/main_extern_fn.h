/* extren mysql fonction   */
extern bool  mysqlInit             (const char *ip) ;
extern int   isExistOnMysql        (const int periode) ;
extern int   verifValue            (const int idLocal) ;
extern bool  InsertIntoMysql       (int dataIndex) ;
extern void  getStationIdByHostName(void) ;

/* extren sqlite fonction   */
extern bool sqliteInit     (const char *dataBaseName) ;
extern bool readHostName   (const char *path, char *hostName) ;
