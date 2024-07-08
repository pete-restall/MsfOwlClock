extern "C"
{
	void *sbrk(void)
	{
		// TODO: Determine whether or not this is needed - do we want to allow malloc() or not ?  Then there's the issue of task-specific heaps...
		return reinterpret_cast<void *>(-1);;
	}
};
