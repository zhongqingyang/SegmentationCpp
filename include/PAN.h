#pragma once
#include"ResNet.h"
#include "PANDecoder.h"

class PANImpl : public torch::nn::Module
{
public:
	PANImpl(int num_classes, std::string encoder_name = "resnet18", std::string pretrained_path = "", int decoder_channels = 32,
		double upsampling = 4);
	torch::Tensor forward(torch::Tensor x);
private:
	ResNet encoder{ nullptr };
	PANDecoder decoder{ nullptr };
	SegmentationHead segmentation_head{ nullptr };
	int num_classes = 1;
	std::vector<int> BasicChannels = { 3, 64, 64, 128, 256, 512 };
	std::vector<int> BottleChannels = { 3, 64, 256, 512, 1024, 2048 };
	std::map<std::string, std::vector<int>> name2layers = getParams();
}; TORCH_MODULE(PAN);


