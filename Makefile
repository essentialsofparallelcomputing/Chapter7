all: HelloOpenMP VecAdd StreamTriad Stencil GlobalSums HighLevelOpenMP_stencil HybridOpenMP_stencil SplitStencil PrefixScan PairwiseSumByTask

HelloOpenMP: HelloOpenMP/HelloOpenMP

HelloOpenMP/HelloOpenMP:
	cd HelloOpenMP; cmake .; make; ./HelloOpenMP; ./HelloOpenMP_fix1; ./HelloOpenMP_fix2; ./HelloOpenMP_fix3; ./HelloOpenMP_fix4; ./HelloOpenMP_fix5

VecAdd: VecAdd/vecadd

VecAdd/vecadd:
	cd VecAdd; cmake .; make; ./vecadd; ./vecadd_opt1; ./vecadd_opt2; ./vecadd_opt3;

StreamTriad: StreamTriad/stream_triad

StreamTriad/stream_triad:
	cd StreamTriad; cmake .; make; ./stream_triad; ./stream_triad_opt1; ./stream_triad_opt2; ./stream_triad_opt3; ./stream_triad_opt4

Stencil: Stencil/stencil

Stencil/stencil:
	cd Stencil; cmake .; make; ./stencil; ./stencil_opt1; ./stencil_opt2

GlobalSums: GlobalSums/globalsums

GlobalSums/globalsums:
	cd GlobalSums; cmake .; make; ./globalsums

HighLevelOpenMP_stencil: HighLevelOpenMP_stencil/stencil_opt2

HighLevelOpenMP_stencil/stencil_opt2:
	cd HighLevelOpenMP_stencil; cmake .; make; ./stencil_opt2; ./stencil_opt3; ./stencil_opt4; ./stencil_opt5; ./stencil_opt6

HybridOpenMP_stencil: HybridOpenMP_stencil/stencil_hybrid

HybridOpenMP_stencil/stencil_hybrid:
	cd HybridOpenMP_stencil; cmake .; make; ./stencil_hybrid; ./stencil_threads

SplitStencil: SplitStencil/SplitStencil

SplitStencil/SplitStencil:
	cd SplitStencil; cmake .; make; ./SplitStencil; ./SplitStencil_opt1

PrefixScan: PrefixScan/PrefixScan

PrefixScan/PrefixScan:
	cd PrefixScan; cmake .; make; ./PrefixScan

PairwiseSumByTask: PairwiseSumByTask/PairwiseSumByTask

PairwiseSumByTask/PairwiseSumByTask:
	cd PairwiseSumByTask; cmake .; make; ./PairwiseSumByTask

clean:
	cd HelloOpenMP; make clean; make distclean
	cd VecAdd; make clean; make distclean
	cd StreamTriad; make clean; make distclean
	cd Stencil; make clean; make distclean
	cd GlobalSums; make clean; make distclean
	cd HighLevelOpenMP_stencil; make clean; make distclean
	cd HybridOpenMP_stencil; make clean; make distclean
	cd SplitStencil; make clean; make distclean
	cd PrefixScan; make clean; make distclean
	cd PairwiseSumByTask; make clean; make distclean
