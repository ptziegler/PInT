#pragma once

#include <HPCPatternInstrASTTraversal.h>
#include "visitor/PatternGraphNodeVisitor.h"

#define PatternMap std::map<clang::CallExpr*, PatternCodeRegion*>

/**
 * The ClangPatternVisitor acts as an adapter between clangs AST visitor and PInTs pattern visitor.<br>
 * Each pattern is associated with two call expressions, representing the Pattern_Begin and Pattern_End
 * functions. This visitor traverses through the AST. Whenever a call expression is encountered, that matches
 * a Pattern_Begin, the Visit methods of the corresponding pattern are called. Analogously, when visiting an
 * expression matching a Pattern_End, the respective EndVisit methods are called.<br>
 * This ensures that the Visit and EndVisit methods are executed in the correct order.
 * @tparam Derived
 */
template <typename Derived> class ClangPatternVisitor : public PatternGraphNodeVisitor, public clang::RecursiveASTVisitor<Derived>{
	private:
		PatternMap PatternBegin;
		PatternMap PatternEnd;

	public:
		explicit ClangPatternVisitor(PatternMap ClangPatternBegin, PatternMap ClangPatternEnd){
			this -> PatternBegin = ClangPatternBegin;
			this -> PatternEnd = ClangPatternEnd;
		}

	//Hookpoint for the Pattern Visitor
	bool TraverseCallExpr(clang::CallExpr* Expression){
		PatternMap::iterator Pattern;

		if((Pattern = PatternBegin.find(Expression)) != PatternBegin.end()){
			VisitPatternCodeRegion(Pattern -> second);
			VisitPatternOccurrence(Pattern -> second -> GetPatternOccurrence());
			VisitParallelPattern(Pattern -> second -> GetPatternOccurrence() -> GetPattern());
			return (true);
		}else if((Pattern = PatternEnd.find(Expression)) != PatternEnd.end()){
			EndVisitPatternCodeRegion(Pattern -> second);
			EndVisitPatternOccurrence(Pattern -> second -> GetPatternOccurrence());
			EndVisitParallelPattern(Pattern -> second -> GetPatternOccurrence() -> GetPattern());
			return (true);
		}else{
			return (clang::RecursiveASTVisitor<Derived>::TraverseCallExpr(Expression));
		}
	}
};
