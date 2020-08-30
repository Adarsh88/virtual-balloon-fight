#include <iostream>
#include <string>
#include <sqlite3.h>

int callback(void *_,int argc,char** argv, char ** azColName){
	for(int i=0;i<argc;i++){
		std::cerr<<azColName[i]<<" = "<<(argv[i]?argv[i]:"NULL");
	}
	std::cerr<<'\n';
	return 0;
} 

int main(){
	sqlite3 *db;
	int rc;
	char *ErrMsg=0;

	rc=sqlite3_open("users.sqlite3",&db);
	

	if(rc){
		std::cerr<<rc<<':';
		std::cerr<<sqlite3_errmsg(db)<<'\n';
	}

	rc=sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users (name TEXT PRIMARY KEY NOT NULL, x INT NOT NULL, y INT NOT NULL);",callback,0,&ErrMsg);
	
	if(rc!=SQLITE_OK){
		std::cerr<<"ERROR: "<<ErrMsg<<"\n";
	}

	//commands:
	// + : add user : `+ <name> <x> <y>`
	// x : attack : `x <x> <y>`
	
	char command;
	std::cin>>command;
	if(command=='+'){
		//TODO
		std::string name;
		std::cin>>name;
		int x,y;
		std::cin>>x>>y;
		sqlite3_stmt *stmt;
		char qry[]="INSERT INTO users VALUES (?,?,?);";
		const char * pzTail=nullptr;
		rc=sqlite3_prepare_v2(db,qry,-1,&stmt,&pzTail);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc=sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_TRANSIENT);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc = sqlite3_bind_int(stmt,2,x);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc = sqlite3_bind_int(stmt,3,y);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc=sqlite3_step(stmt);
		if(rc!=SQLITE_DONE){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc = sqlite3_finalize(stmt);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
	}
	if(command=='x'){
		int x,y;
		std::cin>>x>>y;
		sqlite3_stmt *stmt;
		char zSql[]="SELECT name FROM users WHERE x = ? AND y = ?;";
		char* pzTail;
		rc = sqlite3_prepare_v2(db,zSql,-1,&stmt,(const char **)&pzTail);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc = sqlite3_bind_int(stmt,1,x);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
		rc = sqlite3_bind_int(stmt,2,y);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}

		do{
			rc = sqlite3_step(stmt);

			if(rc!=SQLITE_DONE && rc!=SQLITE_ROW){
				std::cerr<<"ERROR: "<<rc<<"\n";
				std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
			}
			
			std::cout<<sqlite3_column_text(stmt,0)<<std::endl;
		}while(rc==SQLITE_ROW);

		rc = sqlite3_finalize(stmt);
		if(rc!=SQLITE_OK){
			std::cerr<<"ERROR: "<<rc<<"\n";
			std::cerr<<"ERROR: "<<sqlite3_errmsg(db)<<"\n";
		}
	}

	sqlite3_close(db);
}
