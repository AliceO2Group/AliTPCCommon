#ifndef ALIGPUCHAINITS_H
#define ALIGPUCHAINITS_H

#include "AliGPUChain.h"

class AliGPUChainITS : public AliGPUChain
{
	friend class AliGPUReconstruction;
public:
	virtual ~AliGPUChainITS();
	virtual void RegisterPermanentMemoryAndProcessors() override;
	virtual void RegisterGPUProcessors() override;
	virtual int Init() override;
	virtual int Finalize() override;
	virtual int RunStandalone() override;
	
	o2::its::TrackerTraits* GetITSTrackerTraits() {return mITSTrackerTraits.get();}
	o2::its::VertexerTraits* GetITSVertexerTraits() {return mITSVertexerTraits.get();}
	
protected:
	AliGPUChainITS(AliGPUReconstruction* rec);
	std::unique_ptr<o2::its::TrackerTraits> mITSTrackerTraits;
	std::unique_ptr<o2::its::VertexerTraits> mITSVertexerTraits;
};

#endif
