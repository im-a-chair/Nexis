#ifndef NXS_JOBS_H
#define NXS_JOBS_H

//set of worker threads pop from the queue, execute and repeat

///IDEA: maybe (or don't) make it a dynamic system,
    //so you can add a job system add give it a type as ID,
    //this way, all job types stay isolated and you can dynamically manage job types

//Thread (either physical or virtual)
    //physical
    //virtual
    //add option to only use one of two, and general thread division settings
//Job types; default (maily for in, out and proc stage systems), blocking, manual (mostly for one-off or simple one and done tasks)
//Job
    //Func
    //Arg Data
    //Catagory?
//Job Batch
    //completion counter(s)
//Queue -- per thread, uses 'work-stealing' logic
//Context/Manager
    //worker threads
    //blocking threads
    //per-thread queues
//JobState -- to track completion
//Add dedicated job-type and thread for jobs that must block,
    //so those dont intervere with the non blocking jobs.
    //this dedicated thread (could even be multiple),
    //shouldnt be open for stealing jobs from for non blocking threads,
    //so they stay isolated and seperate and dont hurt performance.
    //examples of jobs that would likely be blocking are:
        //scripting system(s)
        //some user systems
        //...

typedef struct NXS_Thread_T {
    //has own queue
    //fibers
} NXS_Thread;
typedef struct NXS_Fiber_T {
    //virtual thread
} NXS_Fiber;
typedef struct NXS_Job_T {
    //function pointer
    //data
} NXS_Job;
typedef struct NXS_JobBatch_T {
    //Jobs
    //counter
    //...
} NXS_JobBatch;
typedef struct NXS_JobQueue_T {
    //count
    //capacity
    //array
    //keep array as last member to allow FAM alloc pattern:
        //= malloc(sizeof(NXS_JobQueue) + sizeof(array_type[disired_lenght]))
} NXS_JobQueue;
typedef struct NXS_JobPool_T {
    //id
    //threads
    //queues per thread
    //batch states
} NXS_JobPool;
typedef struct NXS_JobState_T {
    //...
} NXS_JobState;

//NXS_CreateJobPool
//NXS_DestroyJobPool
//Set/Get JobPool ...
    //thread count
    //fiber count
    //queued job/job-batch count
    //JobState

//NXS_CreateJob
//NXS_DestroyJob
//Set/Get Job ...
//NXS_SubmitJob
//NXS_WaitJob
//NXS_IsJobDone

//NXS_CreateJobBatch
//NXS_DestroyJobBatch
//Set/Get JobBatch ...
//NXS_SubmitJobBatch
//NXS_WaitJobBatch
//NXS_IsJobBatchDone

#endif //NXS_JOBS_H