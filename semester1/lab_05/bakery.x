struct BakeryOrder
{
    int order_num;
    int pid;
    int order_result;
};

program BakeryProgram
{
    version BakeryVerision
    {
        struct BakeryOrder GetOrder(struct BakeryOrder) = 1; 
        struct BakeryOrder WaitInQueue(struct BakeryOrder) = 2;
        struct BakeryOrder ProcessBakeryResult(struct BakeryOrder) = 3;
    } = 1; /* Version number = 1 */
} = 0x20000001;
