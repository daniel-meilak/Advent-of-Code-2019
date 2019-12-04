#ifndef WIRES_H_
#define WIRES_H_

class line_t{
public:
   int xmin;
   int xmax;
   int ymin;
   int ymax;

   // default constructor
   line_t();
};

line_t::line_t(){
   xmin = 0;
   xmax = 0;
   ymin = 0;
   ymax = 0;
}

class path_t{
private:
   void read_instruction(std::string instruction, line_t& line, int& x, int& y);

public:
   std::vector<line_t> lines;

   // constructor
   path_t(std::vector<std::string> input);
};

path_t::path_t(std::vector<std::string> input){

   line_t line;
   int x = 0;
   int y = 0;

   // read each instrunction and create a line
   for (int i=0; i<input.size(); i++){
      read_instruction(input[i], line, x, y);
      lines.push_back(line);
   }
}

void path_t::read_instruction(std::string instruction, line_t& line, int& x, int& y){

   int distance = std::stoi( instruction.substr(1,instruction.size()-1) );

   if ( instruction[0] == 'R' ){
      line.xmin = x;
      x += distance;
      line.xmax = x;
      line.ymin = y;
      line.ymax = y;
   }
   else if ( instruction[0] == 'L' ){
      line.xmax = x;
      x -= distance;
      line.xmin = x;
      line.ymin = y;
      line.ymax = y;
   }
   else if ( instruction[0] == 'U' ){
      line.xmax = x;
      line.xmin = x;
      line.ymin = y;
      y += distance;
      line.ymax = y;
   }
   else if ( instruction[0] == 'D' ){
      line.xmax = x;
      line.xmin = x;
      line.ymax = y;
      y -= distance;
      line.ymin = y;
   }

}

// for (int i=0; i<input_paths.size(); i++){
//    path_t path(input_paths[i]);
//    paths.push_back(path);
// }
//
// for (int i=0; i<paths[0].lines.size(); i++){
//    for (int j=0; j<paths[2].lines.size(); j++){
//
//    }
// }

#endif //WIRES_H_
