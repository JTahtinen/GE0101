#pragma once

class IndexBuffer
{
	unsigned int _id;
	unsigned int _numIndices;
public:
	IndexBuffer();
	void push(const void* data, unsigned int count);
	void bind() const;
	void unbind() const;
	inline unsigned int getSize() const
	{
		return _numIndices;
	}

};