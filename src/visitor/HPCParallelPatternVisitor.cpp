#include "visitor/HPCParallelPatternVisitor.h"
#include "HPCParallelPattern.h"

void VisitParallelPattern(HPCParallelPattern* ParallelPattern){
	static_cast<void>(ParallelPattern); //Avoid unused parameter warning
}

void HPCParallelPatternVisitor::TraverseParallelPattern(HPCParallelPattern* ParallelPattern){
	static_cast<void>(ParallelPattern); //Avoid unused parameter warning
}

void HPCParallelPatternVisitor::EndVisitParallelPattern(HPCParallelPattern* ParallelPattern){
	static_cast<void>(ParallelPattern); //Avoid unused parameter warning
}

void HPCParallelPatternVisitor::HandleParallelPattern(HPCParallelPattern* ParallelPattern){
	VisitParallelPattern(ParallelPattern);
	TraverseParallelPattern(ParallelPattern);
	EndVisitParallelPattern(ParallelPattern);
}
