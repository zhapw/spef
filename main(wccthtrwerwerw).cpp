//
// Created by zhapw on 22-9-26.
//

// Circuits Reader
//#include <experimental/filesystem>


#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>
#include <iostream>
#include <string>
#include <stack>
#include </home/eda/netlist_reader/Parser-SPEF/parser-spef/parser-spef.hpp>

std::string find_name_map(spef::Spef *spef, const std::string& name){
    std::string namenum;
    for (auto iter = spef->name_map.begin(); iter != spef->name_map.end(); ++iter) {
        if(iter->second == name) {
            namenum=std::to_string(iter->first);
        }
    }

    return (namenum);
}
// this is sort of slow ... how can we make it faster?
spef::Net* find_net(spef::Spef *spef,  std::string name) {
    name.insert(0,"*");
    size_t numNets = spef->nets.size();
    for (size_t i = 0; i < numNets; i++) {
        if (spef->nets[i].name == name) {
            return &(spef->nets[i]);
        }
    }

}


#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>
#include <iostream>
#include <string>
#include <stack>
using namespace  std;

struct netlist{
    string _net_name;
    string _output;
    //vector<std::tuple<std::string , double>> input;
    vector<string> _input;
    vector<double> _pin_cap;
    netlist(){}

};

std::vector<std::string> split(std::string s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string& trim(std::string &s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

string removeOuterParentheses(string S) {
    stack<char> mystack;
    char res = '{';
    if(S[0]==res){S.erase(0,1);S.erase(S.end()-1);}
    return S;
}

vector<netlist> read_netlist(char *netlist_info)
{
    char c[150];
    int n=0;
    string input_name;
    string pincap;
    std::tuple<std::string , double> input_tuple;
   // vector<std::tuple<std::string , double>> input_cap;
    netlist net;
    vector<netlist> netlists;
    std::vector<std::string> line;
    int p;

    string ll;
    std::vector<string> tokens;
    string token;



    ifstream file(netlist_info,ios::in | ios::binary);
    if (file.is_open()) {
        while (getline(file,token,':')) {

            std::vector<std::string> split_str = split(token,'\n');

            for (int i=0; i<split_str.size(); i++) {
                tokens.push_back(split_str[i]);

            }

        }

        for(int i=0 ;i<tokens.size();i++){

            if (tokens[i] == "Net name") {
                //  netlists.push_back(net);
                //if(n>=0){netlists.push_back(net);}
                tokens[i+1].erase(0,1);
                net._net_name =  removeOuterParentheses(tokens[i+1]) ;

            }

            if (tokens[i] == "  Output   ") {
                std::vector<std::string> sp = split(tokens[i+1],' ');
                net._output = sp[1];
            }

            if (tokens[i] == "  Input    ") {
                std::vector<std::string> sp = split(tokens[i+1],' ');
                net._input.push_back(sp[1]);
            }

            if (tokens[i] == "  Pin Cap. ") {
                tokens[i+1].erase(0,1);
                net._pin_cap.push_back(stof(tokens[i+1]));
            }


            if (tokens[i].length() == 0) {
                netlists.push_back(net);

                net._input.clear();
                net._pin_cap.clear();

            }

        }

       /* for(int i=0;i<netlists.size();i++){
            cout<<"netlists["<<i<<"]:"<<endl;
            cout<<"net_name is"<<netlists[i]._net_name<<endl;
            cout<<"output is"<<netlists[i]._output<<endl;
            for(int j=0;j<netlists[i]._input.size();j++){
                cout<<"input is"<<netlists[i]._input[j]<<netlists[i]._pin_cap[j]<<endl;}
        }
        */
        }

        file.close();
    return netlists;
}


  //  net.netname="x";
   // net.output="x";
   // net.input[0]="x";
   // net.pincap[0]=0.1;

/*
    ifstream file("/home/eda/netlist_info.txt",ios::in | ios::binary);
    if (file.is_open())
    {
        while (getline(file,ll,':'))
        {

            string l =c;

           if(l.size()!=0) {
               line = split(l, ':');
              // line[0] = trim(line[0]);
               line[1] = trim(line[1]);


               if (line[0] == "Net name") {
                 //  netlists.push_back(net);
                   //if(n>=0){netlists.push_back(net);}

                   net.netname = line[1];
              }

               if (line[0] == "  Output   ") {
                   net.output = line[1];
               }

               if (line[0] == "  Input    ") {

                   net.input.push_back(line[1]);
               }

               if (line[0] == "  Pin Cap. ") {


                  // input_tuple = make_tuple(input_name, stof(pincap));
                   net.pincap.push_back(stof(line[1]));
               }

              // cout<<get<0>(net.input[0])<<endl;
             //  cout<<get<1>(net.input[0])<<endl;



           }  // if(l.size()!=0){netlists.push_back(net);}
            else {
                netlists.push_back(net);
                cout<<"print "<<n<<endl;
                n++;
            }



        }
      // cout << "netlist[4].netname" << netlist[4].netname<<endl;
      //  cout << "netlist[5].output "<<netlist[4].output<<endl;
        file.close();
    }
    cout<<netlists[8].netname<<endl;
    cout<<netlists[8].output<<endl;
  */


struct conn{
    string name;
    int deep1;
    int deep2;
    float cap;
    float dcap;
    int fanout;
    int visited;
    vector<float> pathcap;
    conn()=default;
}co;


int main()
{
    vector<netlist> netlist_info = read_netlist("/home/eda/netlist_info.txt");

 /*   cout<<"netlists["<<2<<"]:"<<endl;
    cout<<"net_name is"<<netlist_info[2]._net_name<<endl;
    cout<<"output is"<<netlist_info[2]._output<<endl;
    for(int j=0;j<netlist_info[2]._input.size();j++){
        cout<<"input is"<<netlist_info[2]._input[j]<<netlist_info[2]._pin_cap[j]<<endl;}
*/
    // SPEF
    char* spef_file = nullptr;
    spef::Spef* spef = nullptr;

    spef_file = "/home/eda/Group0.spef";
    if (spef_file) {

        printf("Reading SPEF file %s\n", spef_file);
        spef = new spef::Spef();
        if (not spef->read(spef_file)) {
            std::cerr << "Error during SPEF processing" << *spef->error << std::endl;
            exit(1);
        }
    }

    cout<<"success!"<<endl;


   // for(int i=0;i<spef->nets.size();i++){
  //      cout<<spef->nets[i].name<<endl;
  //  }
    int n=0;
    for(int i=0;i<netlist_info.size();i++) {
        std::string netnum = find_name_map(spef, netlist_info[i]._net_name);

        cout << "Net_name is" << netnum << endl;

       spef::Net *net = find_net(spef, netnum);
        float load = net->lcap; // in ff
      //   spef::Net* net = find_net(spef, "32520");
        // cout<<load<<endl;
        std::vector<spef::Connection> connections = net->connections;
        std::vector<std::tuple<std::string, std::string, float>> caps = net->caps;
        std::vector<std::tuple<std::string, std::string, float>> ress = net->ress;


        float dcap = 0;
     //   for (auto c: caps) {
      //      dcap = dcap + get<2>(c);
      //  }
      //  cout << "dcap " << dcap << endl;
        // res,loop,visted1,visted2
        std::tuple<int, int, int> ress_mark{0, 0, 0};
        std::tuple<std::string, std::string, float, int, int, int> res_expend{"", "", 0.0, 0, 0, 0};
        vector<std::tuple<std::string, std::string, float, int, int, int>> ress_expend;
        for (auto r: ress) {
            res_expend = tuple_cat(r, ress_mark);
            ress_expend.push_back(res_expend);
        }


        //  for(res=0){

        std::string vn;
        std::string vw;
        deque<string> grey;
        deque<string> black;
        std::vector<std::tuple<std::string, std::string, float>> loop_edge;
        vector<string> endpoint;

        vector<conn> conns;
        string outpin;

        int deep1_before;

        for (int i = 0; i < connections.size(); i++) {
            if (connections[i].direction == spef::ConnectionDirection::OUTPUT) {
                outpin = connections[i].name;
                grey.push_back(outpin);
                black.push_back(outpin);
                break;
            }
        }

        cout<<outpin<<endl;

        co.name = outpin;
        co.deep1 = 0;
        conns.push_back(co);


        while (!grey.empty()) {
            vn = grey.front();
            grey.pop_front();
            int fanout = 0;

            for (auto c: conns) {
                if (c.name == vn) { deep1_before = c.deep1; }
            }


            int end = 1;
            int visited = 0;
            for (auto &c: ress_expend) {
                visited = 0;
                if (std::get<4>(c) != 1) {
                    if (std::get<0>(c) == vn) {

                        for (auto b: black) {
                            if (std::get<1>(c) == b) {
                                visited = 1;
                                std::get<4>(c) = 1;
                                std::get<3>(c) = 1;
                            }
                        }
                        if (visited == 0) {
                            vw = std::get<1>(c);
                            fanout++;
                            grey.push_back(vw);
                            black.push_back(vw);
                            std::get<4>(c) = 1;
                            co.name = vw;
                            co.deep1 = deep1_before + 1;
                            conns.push_back(co);
                            end = -1;
                        }
                    }
                    if (std::get<1>(c) == vn) {

                        for (auto b: black) {
                            if (std::get<0>(c) == b) {
                                visited = 1;
                                std::get<4>(c) = 1;
                                std::get<3>(c) = 1;
                            }
                        }
                        if (visited == 0) {
                            vw = std::get<0>(c);
                            fanout++;
                            grey.push_back(vw);
                            black.push_back(vw);
                            std::get<4>(c) = 1;
                            co.name = vw;
                            co.deep1 = deep1_before + 1;
                            conns.push_back(co);
                            end = -1;
                        }
                    }

                }

            }
            for (auto &c: conns) {
                if (c.name == vn) { c.fanout = fanout; }
            }
            if (end == 1) { endpoint.push_back(vn); }
        }
        // }

        //clear bfs
        grey.clear();
        black.clear();
        //cut loop
        int ip = 0;
        for (auto r: ress_expend) {
            if (get<3>(r) == 1) {
                float x[ip];
                x[ip] = 1;
                string num = to_string(ip);
                std::tuple<std::string, std::string, float> new_res;
                std::tuple<std::string, std::string, float> new_cap;
                string new_res_name = "_" + num;

                //new res new edge
                get<0>(new_res) = get<0>(r);
                get<1>(new_res) = get<1>(r) + new_res_name;
                get<2>(new_res) = get<2>(r);
                ress_expend.push_back(tuple_cat(new_res, ress_mark));
                //new cap  new point
                get<0>(new_cap) = get<1>(new_res);
                get<2>(new_cap) = x[ip];

                endpoint.push_back(get<0>(new_cap));

                caps.push_back(new_cap);

                for (auto &c: conns) { if (c.name == get<0>(r)) { c.fanout = c.fanout + 1; }}
                //new conn
                co.name = get<0>(new_cap);
                for (auto c: conns) { if (c.name == get<0>(new_res)) co.deep1 = c.deep1 + 1; }
                conns.push_back(co);

                vector<string>::iterator it = endpoint.begin();
                while(it!=endpoint.end()){
                    if(*it == get<0>(r)){
                       it = endpoint.erase(find(endpoint.begin(),endpoint.end(),*it));
                    }  else { it++; } }
                ip = ip + 1;
            }
        }

     //   auto iter = remove(endpoint.begin(),endpoint.end(),"0");
        // for(auto r:ress_expend){
        //      cout<<get<0>(r)<<" "<<get<1>(r)<<" "<<get<2>(r)<<" "<<get<3>(r)<<" "<<get<4>(r)<<endl;
        //  }

        // for (auto c: conns) { cout<<c.name<<" "<<c.deep1<<" "<<c.deep2<<" "<<c.cap<<" "<<c.dcap<<" "<<c.visited<<endl;  }

        //  for (auto r: ress_expend) { cout<<get<0>(r)<<" "<<get<1>(r)<<" "<<get<2>(r)<<" "<<get<3>(r)<<" "<<get<4>(r)<<" "<<get<5>(r)<<endl; }
        // for (auto e: endpoint) { cout<<e<<endl; }
        //revse bfs
        int deep2_before;
        int max_deep;

        for (auto &c: conns) {
            for (auto cap: caps) {
                if (c.name == get<0>(cap)) { c.cap = c.dcap = get<2>(cap); }
            }
        }
        // cout<<"pipei"<<endl;
        // for (auto c: conns) { cout<<c.name<<" "<<c.deep1<<" "<<c.deep2<<" "<<c.cap<<" "<<c.dcap<<" "<<c.visited<<endl;  }


        int ini_deep2 = 0;
        for (int i = 0; i < endpoint.size(); i++) {
            for (auto &c: conns) {
                c.deep2 = 0;
                if (c.name == endpoint[i]) {
                    max_deep = c.deep1;

                    //  for (auto &cap: caps) {
                    //        if (get<0>(cap) == endpoint[i])c.cap = get<2>(cap);
                    //       c.dcap = c.cap;
                    c.pathcap.push_back(c.cap);
                    // break;}
                    //    }
                }
            }

            grey.push_back(endpoint[i]);
            black.push_back(endpoint[i]);

            while (!grey.empty()) {
                vn = grey.front();
                grey.pop_front();

                //vn n
                conn n;
                for (auto &c: conns) {
                    if (c.name == vn) {
                        deep2_before = c.deep2;
                        n = c;
                    }
                }

                for (auto &r: ress_expend) {

                    if ((std::get<3>(r) == 0) && (std::get<5>(r) == 0)) {
                        if (std::get<0>(r) == vn) {
                            std::get<5>(r) == 1;
                            vw = std::get<1>(r);
                            for (auto &c: conns) {
                                if (c.name == vw) {
                                    ini_deep2 = c.deep2;
                                    c.deep2 = deep2_before + 1;

                                    if (c.deep1 + c.deep2 == max_deep) {
                                        grey.push_back(vw);

                                        c.pathcap.push_back(c.cap + n.pathcap.back());

                                        c.cap = 0;
                                    } else { c.deep2 = ini_deep2; }
                                }
                            }
                        }

                        if (std::get<1>(r) == vn) {
                            std::get<5>(r) == 1;
                            vw = std::get<0>(r);
                            for (auto &c: conns) {
                                if (c.name == vw) {
                                    ini_deep2 = c.deep2;
                                    c.deep2 = deep2_before + 1;
                                    if (c.deep1 + c.deep2 == max_deep) {
                                        grey.push_back(vw);

                                        c.pathcap.push_back(c.cap + n.pathcap.back());

                                        c.cap = 0;

                                    } else { c.deep2 = ini_deep2; }
                                }
                            }
                        }


                    }
                }
                for (auto &c: conns) {

                    if (c.name == vn) {
                        c.visited = 1;
                    }
                }
            }


        }


        for (auto &c: conns) {
            c.dcap = 0;
            for (int i = 0; i < c.pathcap.size(); i++) {
                c.dcap = c.dcap + c.pathcap[i];
             //   cout<<c.pathcap[i]<<endl;
            }
           // cout<<c.name<<" "<<c.deep1<<" "<<c.deep2<<" "<<c.cap<<" "<<c.dcap<<" "<<c.visited<<endl;
        }


         //   for (auto r: ress_expend) { cout<<get<0>(r)<<" "<<get<1>(r)<<" "<<get<2>(r)<<" "<<get<3>(r)<<" "<<get<4>(r)<<" "<<get<5>(r)<<endl; }
int loopp=0;
        for (auto c: conns) { if (c.name == outpin) { cout << c.name << " " << c.dcap << " " << dcap <<"lcap "<<load<< endl; }}
    for (auto r: ress_expend) { if(get<3>(r)==1) loopp=loopp+1;}
cout<<"loop "<<loopp<<endl;
   // for(auto e:endpoint){cout<<"endpoint "<<e<<endl;}

        vector<conn>(conns).swap(conns);
        connections.clear();
        caps.clear();
        ress.clear();
        ress_expend.clear();
         }




  /*
    std::string netnum = find_name_map(spef, netlist_info[2]._net_name);

    cout<<netnum<<endl;

    spef::Net* net = find_net(spef, netnum);

    */






    return 0;
}