import torch.nn as nn


class ConvNet(nn.Module):
    def __init__(self, num_class=10):
        super(ConvNet, self).__init__()
        pass
        # ----------TODO------------
        # define a network 
        #input B*3*32*32
        self.convnet=nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=32, kernel_size=3, stride=1, padding=1),
        #output B*32*32*32
            nn.ReLU(),
        #output B*32*32*32
            nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, stride=1, padding=1),
        #output B*32*32*64
            nn.ReLU(),
        #output B*32*32*64
            nn.MaxPool2d(kernel_size=2, stride=2),
        #output B*16*16*64
            nn.Conv2d(in_channels=64, out_channels=128, kernel_size=3, stride=1, padding=1),
        #output B*16*16*128
            nn.ReLU(),
        #output B*16*16*128
            nn.Conv2d(in_channels=128, out_channels=256, kernel_size=3, stride=1, padding=1),
        #output B*16*16*256
            nn.ReLU(),
        #output B*16*16*256
            nn.MaxPool2d(kernel_size=2, stride=2)
        )
        #output B*8*8*256
        self.fc=nn.Sequential(
            nn.Linear(8*8*256, 1024),
        #output B*1024
            nn.ReLU(),
        #output B*1024
            nn.Linear(1024, num_class)
        )
        #output B*10
        # ----------TODO------------

    def forward(self, x):

        # ----------TODO------------
        # network forwarding 
        
        x = self.convnet(x)
        x = x.view(x.size(0), -1)
        x = self.fc(x)
        # ----------TODO------------
        
        return x


if __name__ == '__main__':
    import torch
    from torch.utils.tensorboard  import SummaryWriter
    from dataset import CIFAR10
    writer = SummaryWriter(log_dir='../experiments/network_structure')
    net = ConvNet()
    train_dataset = CIFAR10()
    train_loader = torch.utils.data.DataLoader(
        train_dataset, batch_size=2, shuffle=False, num_workers=2)
    # Write a CNN graph. 
    # Please save a figure/screenshot to '../results' for submission.
    for imgs, labels in train_loader:
        writer.add_graph(net, imgs)
        writer.close()
        break 
