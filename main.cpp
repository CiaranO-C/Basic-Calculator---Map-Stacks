 #include <iostream>
 #include <string>
 #include <stack>
 #include <map>
 #include <sstream>


     std::string getExpression() {
     std::cout << "Welcome to the Calculator!\n Please enter an expression below and hit enter.\n";
     std::string userEntry;
     getline(std::cin, userEntry);

     return userEntry;
 }

std::string convertExpression(std::string ex) {
    std::map<std::string, char> opMap;
    opMap["plus"]     = '+';
    opMap["add"]      = '+';
    opMap["subtract"] = '-';
    opMap["minus"]    = '-';
    opMap["times"]    = '*';
    opMap["multiply"] = '*';
    opMap["divide"]   = '/';
    
    std::istringstream inputStream(ex);
    std::string newExpression;
    
    do{
        std::string word;
        inputStream >> word;
        
        if (isdigit(word[0])) {
            newExpression += word;
        } else
            if (opMap.contains(word)) {
                newExpression += opMap[word];
            } else if (word == "+"||word=="-"||word=="/"||word=="*"){
                newExpression += word;
            } else if (word[0] == '(' || word[0] == ')') {
                newExpression += word;
            }
                          
    } while(inputStream);
    std::cout << "new expression is: " << newExpression << '\n';
    
    return newExpression;
}


 int precedence(char x) {
     if (x == '+' || x == '-') return 1;
     if (x == '*' || x == '/') return 2;

         return 0;
 }


 void applyOperator(std::stack<double>& values, std::stack<char>& operators) {
     char op = operators.top();
     operators.pop();
     double value2 = values.top();
     values.pop();
     double value1 = values.top();
     values.pop();

     switch (op) {
         case '+':
             values.push(value1+value2);
             break;
         case '-':
             values.push(value1-value2);
             break;
         case '*':
             values.push(value1*value2);
             break;
         case '/':
             values.push(value1/value2);
             break;
     }

 }




 double calculate(std::string expression){
     std::stack<double> values;
     std::stack<char> operators;

     std::string accumuluate;

     for (char token: expression) {
         if (isdigit(token)) {
             accumuluate += token;
         } else {
             if (!accumuluate.empty()) {
                 values.push(std::stod(accumuluate));
                 accumuluate.clear();
             }
             if (token == '*' || token == '/' || token == '+' || token == '-'){
                 while (!operators.empty() && precedence(operators.top())>= precedence(token)) {
                     applyOperator(values, operators);
                 }
                 operators.push(token);

             }
             else if (token == '(') {
                 operators.push(token);
             }
             else if (token == ')') {
                 while (!operators.empty() && operators.top()!='(') {
                     applyOperator(values, operators);
                 }
                 if (operators.top() == '(') {
                         operators.pop();
                 }
             }
         }
     }
     if (!accumuluate.empty()) {
         values.push(std::stod(accumuluate));
     }
     while (!operators.empty()) {
             applyOperator(values, operators);
     }

     return values.top();
 }








 int main(){
     std::string expression = getExpression();
     double result = calculate(convertExpression(expression));
     std::cout << expression << " = " << result << '\n';

     return 0;
 }
