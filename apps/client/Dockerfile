FROM node:20 AS builder

RUN corepack enable

WORKDIR /app

COPY package.json yarn.lock .yarnrc.yml .

RUN yarn install

COPY . .

RUN yarn build

CMD ["yarn", "start"]