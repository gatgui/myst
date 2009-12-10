

class Parser {
  public:
    Parser();
    ~Parser();
    
    void parseFile(const char *s) {
      yyin = fopen(s, "r");
      YY_NEW_FILE //?
      YY_BUFFER_STATE oldState = YY_CURRENT_BUFFER;
      YY_BUFFER_STATE state = yy_create_buffer(yyin, YY_BUF_SIZE);
      yy_switch_to_buffer(state);
      yylex();
      yy_switch_to_buffer(oldState);
      yy_delete_buffer(state);
      // if done -> yyterminate()
      // what about BEGIN(INITIAL)
      // need to do switch back stuff in the <<EOF>> rule
    }
};
