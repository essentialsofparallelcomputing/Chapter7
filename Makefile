all: HelloOpenMP VecAdd StreamTriad Stencil GlobalSums Private FunctionLevel HighLevelOpenMP_stencil HybridOpenMP_stencil SplitStencil PrefixScan PairwiseSumByTask

HelloOpenMP: HelloOpenMP/build/HelloOpenMP

HelloOpenMP/build/HelloOpenMP:
	cd HelloOpenMP; mkdir build; cd build; cmake ..; make; ./HelloOpenMP; ./HelloOpenMP_fix1; ./HelloOpenMP_fix2; ./HelloOpenMP_fix3; ./HelloOpenMP_fix4; ./HelloOpenMP_fix5

VecAdd: VecAdd/build/vecadd

VecAdd/build/vecadd:
	cd VecAdd; mkdir build; cd build; cmake ..; make; ./vecadd; ./vecadd_opt1; ./vecadd_opt2; ./vecadd_opt3;

StreamTriad: StreamTriad/build/stream_triad

StreamTriad/build/stream_triad:
	cd StreamTriad; mkdir build; cd build; cmake ..; make; ./stream_triad; ./stream_triad_opt1; ./stream_triad_opt2; ./stream_triad_opt3; ./stream_triad_opt4

Stencil: Stencil/build/stencil

Stencil/build/stencil:
	cd Stencil; mkdir build; cd build; cmake ..; make; ./stencil; ./stencil_opt1; ./stencil_opt2

GlobalSums: GlobalSums/build/globalsums

GlobalSums/build/globalsums:
	cd GlobalSums; mkdir build; cd build; cmake ..; make; ./globalsums

Private: Private/build/private

Private/build/private:
	cd Private; mkdir build; cd build; cmake ..; make; ./private

FunctionLevel: FunctionLevel/build/FunctionLevel

FunctionLevel/build/FunctionLevel:
	cd FunctionLevel; mkdir build; cd build; cmake ..; make; ./FunctionLevel; ./FunctionLevelFort

HighLevelOpenMP_stencil: HighLevelOpenMP_stencil/build/stencil_opt2

HighLevelOpenMP_stencil/build/stencil_opt2:
	cd HighLevelOpenMP_stencil; mkdir build; cd build; cmake ..; make; ./stencil_opt2; ./stencil_opt3; ./stencil_opt4; ./stencil_opt5; ./stencil_opt6

HybridOpenMP_stencil: HybridOpenMP_stencil/build/stencil_hybrid

HybridOpenMP_stencil/build/stencil_hybrid:
	cd HybridOpenMP_stencil; mkdir build; cd build; cmake ..; make; ./stencil_hybrid; ./stencil_threads

SplitStencil: SplitStencil/build/SplitStencil

SplitStencil/build/SplitStencil:
	cd SplitStencil; mkdir build; cd build; cmake ..; make; ./SplitStencil; ./SplitStencil_opt1

PrefixScan: PrefixScan/build/PrefixScan

PrefixScan/build/PrefixScan:
	cd PrefixScan; mkdir build; cd build; cmake ..; make; ./PrefixScan

PairwiseSumByTask: PairwiseSumByTask/build/PairwiseSumByTask

PairwiseSumByTask/build/PairwiseSumByTask:
	cd PairwiseSumByTask; mkdir build; cd build; cmake ..; make; ./PairwiseSumByTask

clean:
	cd HelloOpenMP; rm -rf build
	cd VecAdd; rm -rf build
	cd StreamTriad; rm -rf build
	cd Stencil; rm -rf build
	cd GlobalSums; rm -rf build
	cd Private; rm -rf build
	cd FunctionLevel; rm -rf build
	cd HighLevelOpenMP_stencil; rm -rf build
	cd HybridOpenMP_stencil; rm -rf build
	cd SplitStencil; rm -rf build
	cd PrefixScan; rm -rf build
	cd PairwiseSumByTask; rm -rf build
