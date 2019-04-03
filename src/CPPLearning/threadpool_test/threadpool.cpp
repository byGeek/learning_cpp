#include <Windows.h>
#include <stdio.h>

/*
VOID(NTAPI *PTP_WORK_CALLBACK)(
	_Inout_     PTP_CALLBACK_INSTANCE Instance,
	_Inout_opt_ PVOID                 Context,
	_Inout_     PTP_WORK              Work
	);

	*/


void __stdcall work_callback(PTP_CALLBACK_INSTANCE instance, PVOID context, PTP_WORK work) {
	printf("work_callback start\n");
	SleepEx(2000, FALSE);
	printf("work_callback end\n");
}

int main() {

	TP_WORK* pwork = CreateThreadpoolWork(work_callback, NULL, NULL);

	/*
	There is no way to terminate a threadpool thread
	*/

	SubmitThreadpoolWork(pwork);  //submiet work to threadpool

	WaitForThreadpoolWorkCallbacks(pwork, TRUE);

	CloseThreadpoolWork(pwork);

	getchar();

	return 0;
}