#pragma once

class IndexBuffer
{
	unsigned int _id;
public:
	IndexBuffer();
	void push(const void* data, unsigned int count) const;
	void bind() const;
	void unbind() const;
};