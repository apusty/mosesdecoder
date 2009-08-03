#pragma once

/*
 *  Db.h
 *  CreateBerkeleyPt
 *
 *  Created by Hieu Hoang on 29/07/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include <db.h>
#include <db_cxx.h>
#include "Vocab.h"
#include "../../moses/src/TypeDef.h"
#include "../../moses/src/Word.h"

namespace MosesBerkeleyPt
{

class Phrase;
class TargetPhrase;
class Word;
	
class SourceKey
{
public:
	SourceKey(long sourceId, int vocabId)
	:m_sourceId(sourceId)
	,m_vocabId(vocabId)
	{	}
	
	long m_sourceId;
	int m_vocabId;
	
};

class TargetfirKey
{

};


class DbWrapper
{
	Db m_dbMisc, m_dbVocab, m_dbSource, m_dbTarget, m_dbTargetInd;
	Vocab m_vocab;
	long m_nextSourceId, m_nextTargetId;
	int m_numSourceFactors, m_numTargetFactors, m_numScores;

	long SaveSourceWord(long currSourceId, const Word &word);
	
	void SetMisc(const std::string &key, int value);
	int GetMisc(const std::string &key);
	
public:
	DbWrapper();
	~DbWrapper();
	void Open(const std::string &filePath);

	void Save(const Vocab &vocab);
	void SaveSource(const Phrase &phrase, const TargetPhrase &target);
	void SaveTarget(const TargetPhrase &phrase);

	Word *ConvertFromMosesSource(const std::vector<Moses::FactorType> &inputFactorsVec
															 , const Moses::Word &origWord) const;
	Word *CreateSouceWord() const;
	Word *CreateTargetWord() const;
	
	void GetAllVocab();
	
	size_t GetSourceWordSize() const
	{
		return m_numSourceFactors * sizeof(VocabId);
	}
	size_t GetTargetWordSize() const
	{
		return m_numTargetFactors * sizeof(VocabId);
	}
	
	Db &GetSDbMisc()
	{ return m_dbMisc; }
};

}; // namespace

