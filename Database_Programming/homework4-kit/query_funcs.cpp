#include "query_funcs.h"


void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name,
                int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
    string com = "";
    com += "INSERT INTO PLAYER (TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG) VALUES (";
    stringstream ss;
    work W(*C);
    ss << team_id << ", ";
    ss << jersey_num << ", ";
    ss << W.quote(first_name) << ", ";
    ss << W.quote(last_name) << ", ";
    ss << mpg << ", ";
    ss << ppg << ", "; 
    ss << rpg << ", ";
    ss << apg << ", ";
    ss << spg << ", ";
    ss << bpg << "); ";
    com += ss.str();
    W.exec(com);
    W.commit();
}


void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses) {
    string com = "";
    com += "INSERT INTO TEAM (NAME, STATE_ID, COLOR_ID, WINS, LOSSES) VALUES (";
    stringstream ss;
    work W(*C);
    ss<< W.quote(name) << ", ";
    ss << state_id << ", ";
    ss << color_id << ", ";
    ss << wins << ", ";
    ss << losses << "); ";
    com += ss.str();
    W.exec(com);
    W.commit();
}


void add_state(connection *C, string name) {
    string com = "";
    work W(*C);
    com += "INSERT INTO STATE (NAME) VALUES (";
    com +=  W.quote(name);
    com += ");";
    W.exec(com);
    W.commit();   
}


void add_color(connection *C, string name) {
    string com = "";
    work W(*C);
    com += "INSERT INTO COLOR (NAME) VALUES (";
    com +=  W.quote(name);
    com += ");";
    W.exec(com);
    W.commit();  
}

/*
 * All use_ params are used as flags for corresponding attributes
 * a 1 for a use_ param means this attribute is enabled (i.e. a WHERE clause is needed)
 * a 0 for a use_ param means this attribute is disabled
 */
void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            ) {
    //using array to traverse the number
    string com = "";
    com += "SELECT * FROM PLAYER";
    double min1[2] = {min_spg, min_bpg};
    int use[6] = {use_mpg, use_ppg, use_rpg, use_apg, use_spg, use_bpg};
    string variable[6] = {"MPG", "PPG", "RPG", "APG", "SPG", "BPG"};
    bool flag = false;
    int max[4] = {max_mpg, max_ppg, max_rpg, max_apg};
    double max1[2] = {max_spg, max_bpg};
    int min[4] = {min_mpg, min_ppg, min_rpg, min_apg};

    for(int i = 0; i < 6; i++) {
        if(use[i]) {
            if(!flag) {
                com += " WHERE ";
            }
            else {
                com += " AND ";
            }
            if(i < 4) {
                com += variable[i];
                com += " BETWEEN ";
                com += to_string(min[i]);
                com += " AND ";
                //com += variable[i];
                //com += " <= ";
                com += to_string(max[i]);
                flag = true;
            }
            else {
                com += variable[i];
                com += " BETWEEN ";
                com += to_string(min1[i - 4]);
                com += " AND ";
                //com += variable[i];
                //com += " <= ";
                com += to_string(max1[i - 4]);
                flag = true;
            }
        }
    }
    com += ";";
    //use function to get result
    nontransaction N(*C);
    result R(N.exec(com));

    cout << "PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG" << endl;
    result::const_iterator it = R.begin();
    while(it != R.end()) {
        cout << it[0].as<int>() << " ";
        cout << it[1].as<int>() << " ";
        cout << it[2].as<int>() << " ";
        cout << it[3].as<string>() << " ";
        cout << it[4].as<string>() << " ";
        cout << it[5].as<int>() << " ";
        cout << it[6].as<int>() << " "; 
        cout << it[7].as<int>() << " ";
        cout << it[8].as<int>() << " ";
        cout << fixed << setprecision(1) << it[9].as<double>() << " ";
        cout << it[10].as<double>() << endl;
        it++;
    }
}


void query2(connection *C, string team_color) {
    work W(*C);
    string com = "";
    com += "SELECT TEAM.NAME FROM TEAM, COLOR WHERE COLOR.NAME = ";
    com += W.quote(team_color);
    com += "AND TEAM.COLOR_ID = COLOR.COLOR_ID;";
    W.commit();

    //use function to get result
    nontransaction N(*C);
    result R(N.exec(com));

    cout << "NAME" << endl;
    result::const_iterator it = R.begin();
    while(it != R.end()) {
        cout<< it[0].as<string>() << endl;
        it++;
    }
    //stringstream scom;
}


void query3(connection *C, string team_name) {
    work W(*C);
    string com = "";
    com += "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME FROM PLAYER, TEAM WHERE TEAM.NAME = ";
    com += W.quote(team_name);
    com += "AND TEAM.TEAM_ID = PLAYER.TEAM_ID ORDER BY PPG DESC;";
    W.commit();

    //use function to get result
    nontransaction N(*C);
    result R(N.exec(com));

    cout << "FIRST_NAME LAST_NAME" << endl;
    result::const_iterator it = R.begin();
    while(it != R.end()) {
        cout<< it[0].as<string>();
        cout<< " ";
        cout<< it[1].as<string>() << endl;
        it++;
    }
}


void query4(connection *C, string team_state, string team_color) {
    work W(*C);
    string com = "";
    com += "SELECT PLAYER.UNIFORM_NUM, PLAYER.FIRST_NAME, PLAYER.LAST_NAME FROM PLAYER, TEAM, STATE, COLOR WHERE STATE.NAME = ";
    com += W.quote(team_state);
    com += " AND COLOR.NAME = ";
    com += W.quote(team_color);
    com += " AND TEAM.STATE_ID = STATE.STATE_ID AND TEAM.COLOR_ID = COLOR.COLOR_ID ";
    com += "AND TEAM.TEAM_ID = PLAYER.TEAM_ID;";
    W.commit();

    nontransaction N(*C);
    result R(N.exec(com));
    
    cout << "UNIFORM_NUM FIRST_NAME LAST_NAME" << endl;
    result::const_iterator it = R.begin();
    while(it != R.end()) {
        cout << it[0].as<int>() << " ";
        cout << it[1].as<string>() << " ";
        cout << it[2].as<string>() << endl;
        it++;
    }
}

void query5(connection *C, int num_wins) {
    work W(*C);
    string com = "";
    com += "SELECT PLAYER.FIRST_NAME, PLAYER.LAST_NAME, TEAM.NAME, TEAM.WINS FROM PLAYER, TEAM WHERE TEAM.WINS > ";
    com += to_string(num_wins);
    com += " AND TEAM.TEAM_ID = PLAYER.TEAM_ID;";
    W.commit();

    nontransaction N(*C);
    result R(N.exec(com));
    
    cout << "FIRST_NAME LAST_NAME NAME WINS" << endl;
    result::const_iterator it = R.begin();
    while(it != R.end()) {
        cout << it[0].as<string>() << " ";
        cout << it[1].as<string>() << " ";
        cout << it[2].as<string>() <<" ";
        cout << it[3].as<int>() << endl;
        it++;
    }
}

void dropTable(connection *C) {
    //drop table before create
    string com = "";
    vector<string> tableName;
    tableName.push_back("PLAYER");
    tableName.push_back("TEAM");
    tableName.push_back("STATE");
    tableName.push_back("COLOR");
    for(int i = 0; i < 4; i++) {
        com += "DROP TABLE IF EXISTS ";
        com += tableName[i];
        com += " CASCADE;";
        work W(*C);
        W.exec(com);
        W.commit();
    }   
}

void createTable(connection *C) {
    //create state table
    string com3 = "";
    com3 += "CREATE TABLE STATE(";
    com3 += "STATE_ID SERIAL,";
    com3 += "NAME VARCHAR(256),";
    com3 += "PRIMARY KEY (STATE_ID)";
    com3 += ");";
    work W1(*C);
    W1.exec(com3);
    W1.commit();
    //cout<<"after create state table"<<endl;

    //create color table
    string com4 = "";
    com4 += "CREATE TABLE COLOR(";
    com4 += "COLOR_ID SERIAL,";
    com4 += "NAME VARCHAR(256),";
    com4 += "PRIMARY KEY (COLOR_ID)";
    com4 += ");";
    work W2(*C);
    W2.exec(com4);
    W2.commit();
    //cout<<"after create color table"<<endl;

    //create team table
    string com2 = "";
    com2 += "CREATE TABLE TEAM(";
    com2 += "TEAM_ID SERIAL NOT NULL,"; 
    com2 += "NAME VARCHAR(256) NOT NULL,";
    com2 += "STATE_ID INT NOT NULL,"; 
    com2 += "COLOR_ID INT NOT NULL,"; 
    com2 += "WINS INT NOT NULL,"; 
    com2 += "LOSSES INT NOT NULL,";
    com2 += "PRIMARY KEY (TEAM_ID),";
    com2 += "FOREIGN KEY (STATE_ID) REFERENCES STATE(STATE_ID) ON DELETE SET NULL ON UPDATE CASCADE,";
    com2 += "FOREIGN KEY (COLOR_ID) REFERENCES COLOR(COLOR_ID) ON DELETE SET NULL ON UPDATE CASCADE";
    com2 += ")";
    work W3(*C);
    W3.exec(com2);
    W3.commit();
    //cout<<"after create team table"<<endl;

    //create player table
    string com1 = "";
    com1 += "CREATE TABLE PLAYER(";
    com1 += "PLAYER_ID SERIAL NOT NULL,";
    com1 += "TEAM_ID INT NOT NULL,"; 
    com1 += "UNIFORM_NUM INT NOT NULL,";
    com1 += "FIRST_NAME VARCHAR(256) NOT NULL,"; 
    com1 += "LAST_NAME VARCHAR(256) NOT NULL,";
    com1 += "MPG INT NOT NULL,"; 
    com1 += "PPG INT NOT NULL,";
    com1 += "RPG INT NOT NULL,"; 
    com1 += "APG INT NOT NULL,"; 
    com1 += "SPG DOUBLE PRECISION NOT NULL,";
    com1 += "BPG DOUBLE PRECISION NOT NULL,";
    com1 += "PRIMARY KEY (PLAYER_ID),";
    com1 += "FOREIGN KEY (TEAM_ID) REFERENCES TEAM(TEAM_ID) ON DELETE SET NULL ON UPDATE CASCADE";
    com1 += ");";
    work W4(*C);
    W4.exec(com1);
    W4.commit();
}

void proColor(connection * C, const char * file) {
    string row;
    string com = "";
    int COLOR_ID;
    string NAME;
    //open file
    ifstream ifs;
    ifs.open(file);
    if(ifs.is_open()) {
        while(getline(ifs,row)){
            stringstream srow;
	        srow << row;
            //using stringstream to process one line
	        srow >> COLOR_ID;
            srow >> NAME;
            //using function to add into table
	        add_color(C, NAME); 
        }
        ifs.close();
    }
    //cout<<"after process color"<<endl;
}

void proState(connection * C, const char * file) {
    string row;
    string com = "";
    int STATE_ID;
    string NAME;
    //open file
    ifstream ifs;
    ifs.open(file);
    if(ifs.is_open()) {
        while(getline(ifs,row)){
            stringstream srow;
	        srow << row;
            //using stringstream to process one line
	        srow >> STATE_ID;
            srow >> NAME;
            //using function to add into table
	        add_state(C, NAME); 
        }
        ifs.close();
    }
    //cout<<"after process state"<<endl;
}

void proTeam(connection * C, const char * file) {
    string row;
    string com = "";
    int TEAM_ID;
    string NAME;
    int STATE_ID;
    int COLOR_ID;
    int WINS;
    int LOSSES;
    
    //open file
    ifstream ifs;
    ifs.open(file);
    if(ifs.is_open()) {
        while(getline(ifs,row)){
            stringstream srow;
	        srow << row;
            //using stringstream to process one line
	        srow >> TEAM_ID;
            srow >> NAME;
            srow >> STATE_ID;
            srow >> COLOR_ID;
            srow >> WINS;
            srow >> LOSSES;
            //using function to add into table
	        add_team(C, NAME, STATE_ID, COLOR_ID, WINS, LOSSES); 
        }
        ifs.close();
    }
    //cout<<"after process team"<<endl;
}

void proPlayer(connection * C, const char * file) {
    string row;
    string com = "";
    int PLAYER_ID;
    int TEAM_ID;
    int UNIFORM_NUM;
    string FIRST_NAME;
    string LAST_NAME;
    int MPG;
    int PPG;
    int RPG;
    int APG;
    double SPG;
    double BPG;

    //open file
    ifstream ifs;
    ifs.open(file);
    if(ifs.is_open()) {
        while(getline(ifs,row)){
            stringstream srow;
	        srow << row;
            //using stringstream to process one line
	        srow >> PLAYER_ID;
            srow >> TEAM_ID;
            srow >> UNIFORM_NUM;
            srow >> FIRST_NAME;
            srow >> LAST_NAME;
            srow >> MPG;
            srow >> PPG;
            srow >> RPG;
            srow >> APG;
            srow >> SPG;
            srow >> BPG;
	        //using function to add into table
            add_player(C, TEAM_ID, UNIFORM_NUM, FIRST_NAME, LAST_NAME, MPG, PPG, RPG, APG, SPG, BPG); 
        }
        ifs.close();
    }
    //cout<<"after process player"<<endl;
}

void processFile(connection * C) {
    proColor(C, "color.txt");
    proState(C, "state.txt");
    proTeam(C, "team.txt");
    proPlayer(C, "player.txt");
}