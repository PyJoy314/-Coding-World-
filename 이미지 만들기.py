import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
import torch.nn.functional as F

latent_dim = 20
epochs = 50
batch_size = 128
num_classes = 10
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

print(device)

transform = transforms.ToTensor()

train_dataset = datasets.FashionMNIST(root = "./data", download = True, transform = transform)
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)

classes = [
    "T-shirt/top", "Trouser", "Pullover",
    "Dress", "Coat", "Sandal",
    "Shirt", "Sneaker", "Bag", "Ankle boot"
]

print(classes[label])

import matplotlib.pyplot as plt

plt.title(f"{classes[label]}")
plt.imshow(image.reshape(28, 28), cmap = 'gray')
plt.show()

class CVAE(nn.Module):
  def __init__(self, latent_dim = 20, num_classes = 10):
    super(CVAE, self).__init__()
    self.encoder = nn.Sequential(
        nn.Linear(784 + num_classes, 512),
        nn.ReLU(),
        nn.Linear(512, 256),
        nn.ReLU(),
    )
    self.mu = nn.Linear(256, latent_dim)
    self.logvar = nn.Linear(256, latent_dim)
    self.decoder = nn.Sequential(
        nn.Linear(latent_dim + num_classes, 256),
        nn.ReLU(),
        nn.Linear(256, 512),
        nn.ReLU(),
        nn.Linear(512, 784),
        nn.Sigmoid()
    )

  def encode(self, x, c):
    x = x.view(-1, 784)
    combined_input = torch.cat([x, c], dim=1)
    h = self.encoder(combined_input)
    mu = self.mu(h)
    logvar = self.logvar(h)
    return mu, logvar

  def reparameterize(self, mu, logvar):
    std = torch.exp(0.5 * logvar)
    eps = torch.randn_like(std)
    return mu + eps * std

  def decode(self, z, c):
    c_onehot = c
    combined_input = torch.cat([z, c_onehot], dim=1)
    return self.decoder(combined_input)

  def forward(self, x, c):
    mu, logvar = self.encode(x, c)
    z = self.reparameterize(mu, logvar)
    return self.decode(z, c), mu, logvar

def loss_function(recon_x, x, mu, logvar):
  BCE = F.binary_cross_entropy(recon_x, x.view(-1, 784), reduction='sum')
  KLD = -0.5 * torch.sum(1 + logvar - mu.pow(2) - logvar.exp())
  return BCE + KLD

def plot_conditional_generation(model, latent_dim, num_classes=10, num_z=5):
  model.eval()
  fig, axes = plt.subplots(num_z, num_classes, figsize=(1.2 * num_classes, 1.0 * num_z))

  with torch.no_grad():
    for row in range(num_z):
      z_sample = torch.randn(1, latent_dim).to(device)

      for col in range(num_classes):
        target_label = torch.tensor([col]).to(device)
        y_sample = F.one_hot(target_label, num_classes=num_classes).float()

        generated_img = model.decode(z_sample, y_sample)
        generated_img = generated_img.view(28, 28).cpu().numpy()

        axes[row, col].imshow(generated_img, cmap='gray')
        axes[row, col].axis('off')
        axes[row, col].set_aspect('equal')

        if row == 0:
          axes[row, col].set_title(classes[col], fontsize=9, pad=8, rotation=30, ha='center')

  plt.tight_layout()
  plt.show()

from tqdm.notebook import tqdm

model = CVAE(latent_dim=latent_dim).to(device)
optimizer = optim.Adam(model.parameters(), lr=1e-3)


for epoch in range(epochs):
  model.train()
  train_loss = 0
  pbar = tqdm(train_loader, desc=f"{epoch+1} / {epochs}")
  for data, labels in pbar:
    data = data.to(device)

    y_one_hot = F.one_hot(labels.long(), num_classes=num_classes).float().to(device)

    optimizer.zero_grad()
    recon_batch, mu, logvar = model(data, y_one_hot)

    loss = loss_function(recon_batch, data, mu, logvar)
    loss.backward()
    train_loss += loss.item()
    optimizer.step()

    pbar.set_postfix(loss=f"{loss.item():.2f}")
  if epoch % 10 == 0:
    plot_conditional_generation(model, latent_dim, num_classes)
