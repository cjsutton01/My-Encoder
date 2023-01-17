cmake_minimum_required(VERSION 3.23)
project(cs236project3_real_)

set(CMAKE_CXX_STANDARD 14)

add_executable(cs236project3_real_ main.cpp Automaton.h ColonDashAutomaton.cpp ColonDashAutomaton.h CommentAutomaton.cpp CommentAutomaton.h Database.h DatalogProgram.h FactsAutomaton.cpp FactsAutomaton.h Header.h IDAutomaton.h IDAutomaton.cpp Lexer.cpp Lexer.h MachineAutomaton.cpp MachineAutomaton.h Parameter.h Parser.cpp Parser.h Predicate.h QueriesAutomaton.cpp QueriesAutomaton.h Relation.h Rule.h RulesAutomaton.cpp RulesAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h SingleCommentAutomaton.cpp SingleCommentAutomaton.h String.cpp String.h Token.cpp Token.h Tuple.h ColonAutomaton.cpp ColonAutomaton.h Interpreter.h Interpreter.cpp Relation.cpp Graph.h)
