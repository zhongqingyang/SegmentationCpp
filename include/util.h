#ifndef UTIL_H
#define UTIL_H
#undef slots
#include<torch/script.h>
#include<torch/torch.h>
#include "readfile.h"
#define slots Q_SLOTS


inline torch::nn::Conv2dOptions conv_options(int64_t in_planes, int64_t out_planes, int64_t kerner_size,
    int64_t stride = 1, int64_t padding = 0, int groups = 1, bool with_bias = true, int dilation = 1) {
    torch::nn::Conv2dOptions conv_options = torch::nn::Conv2dOptions(in_planes, out_planes, kerner_size);
    conv_options.stride(stride);
    conv_options.padding(padding);
    conv_options.bias(with_bias);
	conv_options.groups(groups);
	conv_options.dilation(dilation);
    return conv_options;
}

inline torch::nn::UpsampleOptions upsample_options(std::vector<double> scale_size,bool align_corners = true){
    torch::nn::UpsampleOptions upsample_options = torch::nn::UpsampleOptions();
    upsample_options.scale_factor(scale_size);
    upsample_options.mode(torch::kBilinear).align_corners(align_corners);
    return upsample_options;
}

inline torch::nn::Dropout2dOptions dropout_options(float p, bool inplace){
    torch::nn::Dropout2dOptions dropoutoptions(p);
    dropoutoptions.inplace(inplace);
    return dropoutoptions;
}

class SegmentationHeadImpl: public torch::nn::Module{
public:
    SegmentationHeadImpl(int in_channels, int out_channels, int kernel_size=3, double upsampling=1);
    torch::Tensor forward(torch::Tensor x);
private:
    torch::nn::Conv2d conv2d{nullptr};
    torch::nn::Upsample upsampling{nullptr};
};TORCH_MODULE(SegmentationHead);

std::string replace_all_distinct(std::string str, const std::string old_value, const std::string new_value);

void load_seg_data_from_folder(std::string folder, std::string image_type,
                               std::vector<std::string> &list_images, std::vector<std::string> &list_labels);

#endif // UTIL_H
